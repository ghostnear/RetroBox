#include "interpreter.hpp"

#define OOON  (opcode & 0x000F)
#define OONO ((opcode & 0x00F0) >> 4)
#define OONN  (opcode & 0x00FF)
#define ONOO ((opcode & 0x0F00) >> 8)
#define ONNN  (opcode & 0x0FFF)
#define NOOO ((opcode & 0xF000) >> 12)
#define  VF  (state -> V[0x0F])
#define  VY  (state -> V[OONO])
#define  VX  (state -> V[ONOO])
#define  VPC (state -> PC)
#define  VI  (state -> I)

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
                switch(OONN)
                {
                // CLS
                case 0xE0:
                    memset(state -> VRAM, 0, state -> screen_h * state -> screen_w);
                    break;

                // RET
                case 0xEE:
                    state -> sp--;
                    VPC = *state -> sp;
                    break;

                default:
                    goto opcode_unknown;
                    break;
                }
                break;
            
            // JMP NNN
            case 0x1:
                VPC = ONNN;
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

            // RND VX, NN
            case 0xC:
                VX = ((uint8_t)rand()) & OONN;
                break;

            // DRW VX, VY, N
            case 0xD:
                for(auto i = 0; i < OOON; i++)
                {
                    for(auto j = 0; j < 8; j++)
                    {
                        // Check if bit is set in sprite
                        if(state -> RAM[VI + i] & (1 << (7 - j)))
                        {
                            // Collision flag
                            VF = ((state -> VRAM[(VY + i) * state -> screen_w + VX + j] == 1) ? 1 : VF);

                            // XOR the pixel
                            state -> VRAM[(VY + i) * state -> screen_w + VX + j] ^= 1;
                        }
                    }
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

                // LD DT, VX
                case 0x15:
                    state -> delta_timer = VX;
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
