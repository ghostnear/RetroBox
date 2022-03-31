#ifndef CHIP8_CPU_INTERPRETER_HPP
#define CHIP8_CPU_INTERPRETER_HPP

#include <string>
#include <chrono>
#include <thread>
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
            std::thread* run_thread = nullptr;
        public:
            void tick(double dt);
            void start() override;
            void stop() override;
            void step() override;
            void update(double dt) override;
        };
    };
}

#endif