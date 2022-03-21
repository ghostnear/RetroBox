#ifndef CHIP8_CPU_INTERPRETER_HPP
#define CHIP8_CPU_INTERPRETER_HPP

#include <string>
#include <cstdlib>
#include "cpu.hpp"

namespace Emulators
{
    namespace Components
    {
        class CHIP8Interpreter : public CHIP8CPU
        {
        private:
            double timer = 0, timer_60hz = 0;
        public:
            void step() override;
            void update(double dt) override;
        };
    };
}

#endif