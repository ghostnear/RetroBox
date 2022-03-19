#ifndef CHIP8_STATE_HPP
#define CHIP8_STATE_HPP

#include <cstdint>

namespace Emulators
{
    namespace Components
    {
        enum CHIP8Specs
        {
            CHIP8 = 1 << 0
        };

        class CHIP8State
        {
        private:
            int32_t enabledSpecs = 1;
            
        public:
            /// Spec ops
            void disableSpec(CHIP8Specs spec);
            void enableSpec(CHIP8Specs spec);
            bool checkSpec(CHIP8Specs spec);
        };
    };
};

#endif