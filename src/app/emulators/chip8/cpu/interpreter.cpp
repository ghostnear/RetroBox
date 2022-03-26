#include "interpreter.hpp"

#define OOON  (opcode & 0x000F)
#define OONO ((opcode & 0x00F0) >> 4)
#define OONN  (opcode & 0x00FF)
#define ONOO ((opcode & 0x0F00) >> 8)
#define ONNN  (opcode & 0x0FFF)
#define NOOO ((opcode & 0xF000) >> 12)
#define  VF  (state -> V[0x0F])
#define  VO  (state -> V[0x00])
#define  VY  (state -> V[OONO])
#define  VX  (state -> V[ONOO])
#define  VPC (state -> PC)
#define  VI  (state -> I)

#define clean() \
    memset(state -> VRAM, 0, state -> screen_h * state -> screen_w);

#define resize(newX, newY) \
    state -> screen_w = newX; \
    state -> screen_h = newY; \
    if(state -> VRAM) \
        delete state -> VRAM; \
    state -> VRAM = new uint8_t[newX * newY]; \
    clean();

namespace Emulators
{
    namespace Components
    {
        void CHIP8Interpreter::step()
        {
            // Fetch opcode from current PC and advance
            uint16_t opcode = (state -> RAM[VPC] << 8) | state -> RAM[VPC + 1];
            VPC += 2;

            // Check opcode
            switch(NOOO)
            {
            // System ops
            case 0x0:
                // Clean hires
                if(opcode == 0x0230)
                    memset(state -> VRAM, 0, state -> screen_h * state -> screen_w);
                else
                {
                    switch(OONN)
                    {
                    // CLS
                    case 0xE0:  clean();  break;

                    // RET
                    case 0xEE:
                        state -> sp--;
                        VPC = *state -> sp;
                        break;

                    /// SCR
                    case 0xFB:
                        for(auto i = 0; i < state -> screen_h; i++)
                        {
                            memmove(
                                state -> VRAM + i * state -> screen_w + 4,
                                state -> VRAM + i * state -> screen_w,
                                state -> screen_w - 4);
                            memset(state -> VRAM + i * state -> screen_w, 0, 4);
                        }
                        break;

                    /// SCL
                    case 0xFC:
                        for(auto i = 0; i < state -> screen_h; i++)
                        {
                            memmove(
                                state -> VRAM + i * state -> screen_w,
                                state -> VRAM + i * state -> screen_w + 4,
                                state -> screen_w - 4);
                            memset(state -> VRAM + (i + 1) * state -> screen_w - 4, 0, 4);
                        }
                        break;

                    // HIGH
                    case 0xFF:
                        resize(128, 64);
                        break;

                    default:
                        switch(OONO)
                        {
                        // SCD N
                        case 0xC:
                            memmove(
                                state -> VRAM + OOON * state -> screen_w,
                                state -> VRAM,
                                state -> screen_w * (state -> screen_h - OOON));
                            memset(state -> VRAM, 0, OOON * state -> screen_w);
                            break;
                        default:
                            goto opcode_unknown;
                            break;
                        }
                        break;
                    }
                }
                break;
            
            // JMP NNN
            case 0x1:
                // Init hires
                if(opcode == 0x1260) { resize(64, 64); }
                else    VPC = ONNN;
                break;

            // CALL NNN
            case 0x2:
                *state -> sp = VPC;
                state -> sp++;
                VPC = ONNN;
                break;
            
            // SE VX, NN
            case 0x3:
                VPC += 2 * (VX == OONN);
                break;

            // SNE VX, NN
            case 0x4:
                VPC += 2 * (VX != OONN);
                break;
            
            // Register ops
            case 0x5:
                switch(OOON)
                {
                // SE VX, VY
                case 0x0:
                    VPC += 2 * (VX == VY);
                    break;

                default:
                    goto opcode_unknown;
                    break;
                }
                break;

            // LD VX, NN
            case 0x6:
                VX = OONN;
                break;

            // ADD VX, NN
            case 0x7:
                VX += OONN;
                break;

            // More register ops
            case 0x8:
                switch(OOON)
                {
                // LD VX, VY
                case 0x0:
                    VX = VY;
                    break;
                
                // OR VX, VY
                case 0x1:
                    VX |= VY;
                    break;

                // AND VX, VY
                case 0x2:
                    VX &= VY;
                    break;

                // XOR VX, VY
                case 0x3:
                    VX ^= VY;
                    break;

                // ADD VX, VY
                case 0x4:
                    VF = (0xFF - VY) > VX;
                    VX += VY;
                    break;

                // SUB VX, VY
                case 0x5:
                    VF = VX > VY;
                    VX -= VY;
                    break;

                // SHR VX, VY
                case 0x6:
                    VF = VX & 1;
                    VX >>= 1;
                    break;

                // SUBN VX, VY
                case 0x7:
                    VF = VX > VY;
                    VX = VY - VX;
                    break;

                // SHL VX, VY
                case 0xE:
                    VF = ((VX & (1 << 8)) != 0);
                    VX <<= 1;
                    break;

                default:
                    goto opcode_unknown;
                    break;
                }
                break;

            // Register ops again
            case 0x9:
                switch(OOON)
                {
                // SE VX, VY
                case 0x0:
                    VPC += 2 * (VX != VY);
                    break;

                default:
                    goto opcode_unknown;
                    break;
                }
                break;

            // LD I, NNN
            case 0xA:
                VI = ONNN;
                break;

            // JMP V0, NNN
            case 0xB:
                VPC = ONNN + VO;
                break;

            // RND VX, NN
            case 0xC:
                VX = ((uint8_t)rand()) & OONN;
                break;

            // DRW VX, VY, N
            case 0xD:
                VF = 0;
                if(OOON != 0)
                {
                    for(auto i = 0; i < OOON; i++)
                    {
                        for(auto j = 0; j < 8; j++)
                        {
                            // Check if bit is set in sprite
                            if(state -> RAM[VI + i] & (1 << (7 - j)))
                            {
                                // Pixel pos
                                uint32_t pos = (VY + i) * state -> screen_w + VX + j;
                                pos %= state -> screen_w * state -> screen_h;

                                // Collision flag
                                VF = ((state -> VRAM[pos] == 1) ? 1 : VF);

                                // XOR the pixel
                                state -> VRAM[pos] ^= 1;
                            }
                        }
                    }
                }
                else
                {
                    for(auto i = 0; i < 0x10; i++)
                    {
                        for(auto j = 0; j < 0x10; j++)
                        {
                            // Check if bit is set in sprite
                            if((j < 8 && state -> RAM[VI + 2 * i] & (1 << (7 - j))) || (j >= 8 && state -> RAM[VI + 2 * i + 1] & (1 << (0xF - j))))
                            {
                                // Pixel pos
                                uint32_t pos = (VY + i) * state -> screen_w + VX + j;
                                pos %= state -> screen_w * state -> screen_h;

                                // Collision flag
                                VF = ((state -> VRAM[pos] == 1) ? 1 : VF);

                                // XOR the pixel
                                state -> VRAM[pos] ^= 1;
                            }
                        }
                    }
                }
                
                break;
            
            // Input handling
            case 0xE:
                switch(OONN)
                {
                // SKP VX
                case 0x9E:
                    VPC += 2 * (state -> keys[VX]);
                    break;

                // SKNP VX
                case 0xA1:
                    VPC += 2 * (!state -> keys[VX]);
                    break;

                default:
                    goto opcode_unknown;
                    break;
                }
                break;

            // Special ops
            case 0xF:
                switch(OONN)
                {
                // LD VX, DT
                case 0x07:
                    VX = state -> delta_timer;
                    break;

                // LD VX, KEY
                case 0x0A:
                    VX = 0x10;
                    for(auto i = 0; i < 0x10 && VX == 0x10; i++)
                        if(state -> keys[i])
                            VX = i;
                    VPC -= 2 * (VX == 0x10);
                    break;

                // LD DT, VX
                case 0x15:
                    state -> delta_timer = VX;
                    break;

                // LD ST, VX
                case 0x18:
                    state -> sound_timer = VX;
                    break;

                // ADD I, VX
                case 0x1E:
                    VF = VI > 0x0FFF;
                    VI += VX;
                    break;

                // LD I, FONT(VX)
                case 0x29:
                    VI = VX * 5;
                    break;
                
                // LD I, SFONT(VX)
                case 0x30:
                    VI = 5 * 0x10 + VX * 10;
                    break;

                // BCD VX
                case 0x33:
                    state -> RAM[VI] = (VX / 100);
                    state -> RAM[VI + 1] = ((VX / 10) % 10);
                    state -> RAM[VI + 2] = (VX % 10);
                    break;

                // LD [I], VX
                case 0x55:
                    memcpy(state -> RAM + VI, state -> V, ONOO + 1);
                    break;

                // LD VX, [I]
                case 0x65:
                    memcpy(state -> V, state -> RAM + VI, ONOO + 1);
                    break;

                default:
                    goto opcode_unknown;
                    break;
                }
                break;

            default:
                goto opcode_unknown;
                break;
            }

            return;
            
            opcode_unknown:
                addToLog("Unknown opcode detected! " + Core::Utils::convertToHex(opcode, 4));
        }

        void CHIP8Interpreter::update(double dt)
        {
            if(state -> running)
            {
                timer += dt;
                while(timer >= 1.0 / state -> speed)
                {
                    step();
                    timer -= 1.0 / state -> speed;
                }
                    
                timer_60hz += dt;
                while(timer_60hz >= 1.0 / 60)
                {
                    state -> sound_timer -= (state -> sound_timer > 0);
                    state -> delta_timer -= (state -> delta_timer > 0);
                    timer_60hz -= 1.0 / 60;
                }
            }
            else timer = timer_60hz = 0;
        }
    };
}
