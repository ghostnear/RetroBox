#include "header/chip8.hpp"

namespace Emulators
{
    void CHIP8::init()
    {
        parent -> getWindow() -> setWindowTitle("Owari | CHIP8");
        state = new CHIP8State();
        cpu = new CHIP8Interpreter();
        cpu -> attachState(state);
    }

    void CHIP8::draw()
    {
        if(state -> debugging)
        {
            ImGui::Begin("CHIP8 Debugger");
            ImGui::Text("Performance: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            if(ImGui::CollapsingHeader("Controls"))
            {
                if(ImGui::BeginTable("controls_table", 3))
                {
                    // Speed controls
                    ImGui::TableNextColumn();
                    ImGui::InputInt("Speed (inst / s)", &state -> speed, 5);
                    if(state -> speed < 1) state -> speed = 1;

                    if(state -> running)
                    {
                        ImGui::TableNextColumn();
                        if(ImGui::Button("Stop"))
                            state -> running = false;
                    }
                    else
                    {
                        ImGui::TableNextColumn();
                        if(ImGui::Button("Start"))
                            state -> running = true;
                        ImGui::TableNextColumn();
                        if(ImGui::Button("Step"))
                            cpu -> step();        
                    }
                    ImGui::EndTable();
                }
            }
            cpu -> printLog();
            state -> draw();
            ImGui::End();
        }
    }

    void CHIP8::loadROM(std::string path)
    {
        std::ifstream fin(path.c_str(), std::ios::binary | std::ios::ate);
        if(fin.fail())
        {
            std::string output = "Could not load ROM at path: " + path + "\nContinuing without a ROM...";
            Core::show_error_window(output.c_str(), parent -> getWindow() -> getSDL());
        }
        else
        {
            // Get the file size
            int32_t size = 0;
            size = fin.tellg();
            fin.seekg(std::ios::beg);

            // Check if the ROM is small enough to load
            if(0x1000 - state -> mountPoint < size)
            {
                std::string output = "The ROM at path: " + path + " is too big.\n";
                output += "Size: " + std::to_string(size) + "b\n";
                output += "Max size: " + std::to_string(0x1000 - state -> mountPoint) + "b\n";
                output += "Continuing without a ROM...";
                Core::show_error_window(output.c_str(), parent -> getWindow() -> getSDL());
            }
            else
                fin.read(reinterpret_cast<char*>(state -> RAM + state -> mountPoint), size);
        }
        fin.close();
    }
    
    void CHIP8::update(double dt)
    {
        cpu -> update(dt);
    }
};