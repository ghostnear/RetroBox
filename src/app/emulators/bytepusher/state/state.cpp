#include "state.hpp"

namespace Emulators
{
    namespace Components
    {
        BytePusherState::BytePusherState()
        {
            reset();
        }

        void BytePusherState::reset()
        {
            // Allocate memory
            RAM = new uint8_t[RAM_size];
            memset(keys, 0, 0x10);

            // Not running
            running = false;
        }
    };
};