#include "state.hpp"

namespace Emulators
{
    namespace Components
    {
        void CHIP8State::disableSpec(CHIP8Specs spec)
        {
            enabledSpecs &= ~((int32_t)spec);
        }

        void CHIP8State::enableSpec(CHIP8Specs spec)
        {
            enabledSpecs |= (int32_t)spec;
        }

        bool CHIP8State::checkSpec(CHIP8Specs spec)
        {
            return ((enabledSpecs & spec) != 0);
        }
    };
};