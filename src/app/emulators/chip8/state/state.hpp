#ifndef CHIP8_STATE_HPP
#define CHIP8_STATE_HPP

#include <cstdint>
#include <imgui.h>
#include <imgui_memory_editor.h>

namespace Emulators
{
    namespace Components
    {
        enum CHIP8Specs
        {
            CHIP8 = 1 << 0,
            SCHIP8 = 1 << 1
        };

        class CHIP8State
        {
        private:
            // CPU instruction specs
            int32_t enabledSpecs = 1;

            // Registers
            uint8_t V[0x10];
            uint16_t PC;

            // RAM
            uint8_t RAM[0x1000];
            
        public:
            bool debugging = true;

            // Constructor
            CHIP8State();

            // Resets the state to the default values
            void reset();

            /// Spec ops
            void disableSpec(CHIP8Specs spec);
            void enableSpec(CHIP8Specs spec);
            bool checkSpec(CHIP8Specs spec);

            /// Draw in ImGui mode
            void draw();
        };
    };
};

#endif