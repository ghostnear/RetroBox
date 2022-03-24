#include "header/chip8.hpp"

namespace Emulators
{
    void CHIP8::init()
    {
        parent -> getWindow() -> setWindowTitle("Owari | CHIP8");
        state = new CHIP8State();
        cpu = new CHIP8Interpreter();
        cpu -> attachState(state);
        srand(time(NULL));
    }

    void CHIP8::draw()
    {
        // Get the renderer
        SDL_Renderer* ren = parent -> getWindow() -> getRenderer() -> getSDL();

        ///TODO: fix this mess

        // Check display if it needs updates
        if(lscreen_w != state -> screen_w || lscreen_h != state -> screen_h)
        {
            lscreen_w = state -> screen_w;
            lscreen_h = state -> screen_h;
            if(tex)
                SDL_DestroyTexture(tex);
            tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, lscreen_w, lscreen_h);
        }

        // Draw the screen to the texture
        void* mPixels;
        int mPitch;
        SDL_LockTexture(tex, NULL, &mPixels, &mPitch);
        Uint32 *pixeldata = (Uint32 *)mPixels;
        for(auto i = 0; i < lscreen_w; i++)
            for(auto j = 0; j < lscreen_h; j++)
            {
                if(state -> VRAM[i + j * lscreen_w])
                    pixeldata[i + j * lscreen_w] = 0xFFFFFFFF;
                else
                    pixeldata[i + j * lscreen_w] = 0x000000FF;
            }
        SDL_UnlockTexture(tex);

        // Draw texture to the screen
        SDL_Rect r;
        int minFit = std::min(ImGui::GetIO().DisplaySize.x / lscreen_w, ImGui::GetIO().DisplaySize.y / lscreen_h);
        r.w = lscreen_w * minFit;
        r.h = lscreen_h * minFit;
        r.x = (ImGui::GetIO().DisplaySize.x - r.w) / 2;
        r.y = (ImGui::GetIO().DisplaySize.y - r.h) / 2;
        SDL_SetRenderDrawColor(ren, 16, 16, 16, 255);
        SDL_SetRenderTarget(ren, NULL);
        SDL_RenderCopy(ren, tex, NULL, &r);

        // If debugging is enabled
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
                    if(state -> speed > 10000) state -> speed = 10000;

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
        // Update the input
        Core::Input* input = parent -> getWindow() -> getInput();
        for(auto i = 0; i < 0x10; i++)
            state -> keys[i] = input -> getKey(state -> keyBind[i]);

        // Check for debug key press
        if(input -> getKeyPressed(state -> debugBind))
            state -> debugging = !state -> debugging;

        // Update the CPU
        cpu -> update(dt);
    }
};