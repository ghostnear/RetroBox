#include "interpreter.hpp"

#define OXOO(o) ((o & 0x0F00) >> 8)
#define OONN(o) (o & 0x00FF)
#define ONNN(o) (o & 0x0FFF)

namespace Emulators
{
    namespace Components
    {
        void CHIP8Interpreter::step()
        {
            // Fetch opcode from current PC and advance
            uint16_t opcode = (state -> RAM[state -> PC] << 8) | state -> RAM[state -> PC + 1];
            state -> PC += 2;

            // Check opcode
            switch(opcode & 0xF000)
            {
            case 0x0000:
                goto opcode_error;
                break;

            // LD VX, NN
            case 0x6000:
                state -> V[OXOO(opcode)] = OONN(opcode);
                break;

            // LD I, NNN
            case 0xA000:
                state -> I = ONNN(opcode);
                break;

            default:
                goto opcode_error;
                break;
            }

            return;
            
            opcode_error:
                addToLog("Unknown opcode detected! " + Core::Utils::convertToHex(opcode, 4));
        }

        void CHIP8Interpreter::update(double dt)
        {

        }
    };
}
