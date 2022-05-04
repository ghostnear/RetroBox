#ifndef BYTEPUSHER_STATE_HPP
#define BYTEPUSHER_STATE_HPP

#include <cstdint>
#include <imgui.h>
#include <core.hpp>

namespace Emulators
{
    namespace Components
    {
        class BytePusherState
        {
        public:
            // VM memory
            uint8_t *RAM;
            uint32_t RAM_size = 0xFFFFFF;

            // Color palette
            SDL_Color palette[256];

            // Keybinds
            char keyBind[0x10] = { 'x', '1', '2', '3', 'q', 'w', 'e', 'a', 's', 'd', 'z', 'c', '4', 'r', 'f', 'v'};
            int32_t speed = 60;
            uint8_t keys[0x10];
            bool draw_flag = false;

            // If the emulator is running
            bool running = false;

            // Constructor
            BytePusherState();

            // Resets the state to the default values
            void reset();

            /// Draw in ImGui mode
            void draw();
        };
    };
};

#endif