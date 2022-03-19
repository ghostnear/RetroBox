#ifndef CHIP8_CPU_INTERPRETER_HPP
#define CHIP8_CPU_INTERPRETER_HPP

#include "cpu.hpp"

namespace Emulators
{
    namespace Components
    {
        class CHIP8Interpreter : public CHIP8CPU
        {
        protected:
            CHIP8State* state;
        public:
            void attachState(CHIP8State* newState) { state = newState; }
            void update(double dt) override;
        };
    };
}

#endif