#include "state.hpp"

namespace Emulators
{
    namespace Components
    {
        CHIP8State::CHIP8State()
        {
            reset();
        }

        void CHIP8State::reset()
        {
            const uint8_t defaultFont[] = {
                0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                0x20, 0x60, 0x20, 0x20, 0x70, // 1
                0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                0xF0, 0x80, 0xF0, 0x80, 0x80, // F
            };

            // Set to the default values
            stack = new uint8_t[0x10];
            sp = stack;
            memset(V, 0, 0x10);
            memset(stack, 0, 0x10);
            memset(RAM, 0, 0x1000);
            memcpy(RAM, defaultFont, 5 * 0x10);
            PC = mountPoint;
            I = 0;

            // Initialise display values
            screen_w = 64;
            screen_h = 32;
            if(VRAM)
                delete VRAM;
            VRAM = new uint8_t[screen_w * screen_h];
            memset(VRAM, 0, screen_h * screen_w);
        }

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

        void CHIP8State::draw()
        {
            if(ImGui::CollapsingHeader("Enabled specs"))
            {
                if(ImGui::BeginTable("spec_table", 5))
                {
                    if(CHIP8State::checkSpec(CHIP8Specs::CHIP8))
                        { ImGui::TableNextColumn(); ImGui::Text("CHIP8"); }
                    if(CHIP8State::checkSpec(CHIP8Specs::SCHIP8))
                        { ImGui::TableNextColumn(); ImGui::Text("SCHIP8"); }
                    ImGui::EndTable();
                }
            }
            if(ImGui::CollapsingHeader("Registers"))
            {
                if(ImGui::BeginTable("registers_table", 4))
                {
                    for(int i = 0; i < 0x10; i++)
                    {
                        ImGui::TableNextColumn();
                        ImGui::Text("V[%01X] =  %03d", i, V[i]);
                    }
                    ImGui::TableNextColumn(); ImGui::Text("PC =  %04X", PC);
                    ImGui::TableNextColumn(); ImGui::Text("I =  %04X", I);
                    ImGui::EndTable();
                }
                ImGui::Text("Stack");
                if(ImGui::BeginTable("stack_table", 8))
                {
                    for(int i = 0; i < 0x10 && stack + i < sp; i++)
                    {
                        ImGui::TableNextColumn();
                        ImGui::Text("%s", Core::Utils::convertToHex(stack[i], 3).c_str());
                    }
                    ImGui::EndTable();
                }
            }
            if(ImGui::CollapsingHeader("VRAM"))
            {
                if(ImGui::BeginTable("vram_table", screen_w))
                {
                    for(int i = 0; i < screen_h; i++)
                    {
                        for(int j = 0; j < screen_w; j++)
                        {
                            ImGui::TableNextColumn();
                            if(VRAM[i * screen_w + j])
                                ImGui::Text("*");
                            else
                                ImGui::Text(" ");
                        }
                    }
                    ImGui::EndTable();
                }
            }
            if(ImGui::CollapsingHeader("Memory"))
            {
                mem_edit.ReadOnly = true;
                mem_edit.HighlightMin = PC;
                mem_edit.HighlightMax = PC + 2;
                mem_edit.HighlightColor = IM_COL32(255, 0, 0, 125);
                ///TODO: support viewing of the I register in the memory view somehow, would be nice
                mem_edit.DrawContents(RAM, 0x1000);
            }
        }
    };
};