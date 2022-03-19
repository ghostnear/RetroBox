#ifndef CHIP8_CPU_INTERPRETER_HPP
#define CHIP8_CPU_INTERPRETER_HPP

#include <string>
#include "cpu.hpp"

namespace Emulators
{
    namespace Components
    {
        class CHIP8Interpreter : public CHIP8CPU
        {
        public:
            void step() override;
            void update(double dt) override;
        };
    };
}

#endif