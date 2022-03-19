#ifndef CHIP8_CPU_HPP
#define CHIP8_CPU_HPP

#include "../state/state.hpp"

namespace Emulators
{
    namespace Components
    {
        class CHIP8CPU
        {
        protected:
            CHIP8State* state;
        public:
            void attachState(CHIP8State* newState) { state = newState; }
            virtual void update(double dt) = 0;
        };

        enum CHIP8ExecutionMode
        {
            Interpreter = 0
        };
    };
};

#endif