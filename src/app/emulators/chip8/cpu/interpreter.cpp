#include "interpreter.hpp"

#define OOON  (opcode & 0x000F)
#define OONO ((opcode & 0x00F0) >> 4)
#define OONN  (opcode & 0x00FF)
#define ONOO ((opcode & 0x0F00) >> 8)
#define ONNN  (opcode & 0x0FFF)
#define NOOO ((opcode & 0xF000) >> 12)
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

            // LD VX, NN
            case 0x6:
                VX = OONN;
                break;

            // ADD VX, NN
            case 0x7:
                VX += OONN;
                break;

            // Register ops
            case 0x8:
                switch(OOON)
                {
                // LD VX, VY
                case 0x0:
                    VX = VY;
                    break;

                // AND VX, VY
                case 0x2:
                    VX &= VY;
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

            // DRW VX, VY, N
            case 0xD:
                for(auto i = 0; i < OOON; i++)
                {
                    for(auto j = 0; j < 8; j++)
                    {
                        // Check if bit is set in sprite
                        if(state -> RAM[VI + i] & (1 << (7 - j)))
                        {
                            // XOR the pixel
                            state -> VRAM[(VY + i) * state -> screen_w + VX + j] ^= 1;
                        }
                    }
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
                    step(), timer -= 1.0 / state -> speed;
            }
            else timer = 0;
        }
    };
}
