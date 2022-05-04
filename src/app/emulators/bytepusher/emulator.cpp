#include "header/bytepusher.hpp"

#define min_fit \
    (std::min(ImGui::GetIO().DisplaySize.x / 256, ImGui::GetIO().DisplaySize.y / 256))

namespace Emulators
{
    void BytePusher::init()
    {
        parent -> getWindow() -> setWindowTitle(APP_NAME + " | BytePusher");
        state = new BytePusherState();
        vm = new BytePusherVM();
        vm -> attachState(state);
    }

    void BytePusher::draw()
    {
        // Get the renderer
        SDL_Renderer* ren = parent -> getWindow() -> getRenderer() -> getSDL();

        // Check if display exists
        if(!tex)
            tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, 256, 256);

        // Draw the screen to the texture
        if(state -> draw_flag)
        {
            void* mPixels;
            int mPitch;
            SDL_LockTexture(tex, NULL, &mPixels, &mPitch);

            // TODO: drawing

            SDL_UnlockTexture(tex);
            state -> draw_flag = false;
        }

        // Draw texture to the screen
        SDL_Rect r;
        r.w = 256 * min_fit;
        r.h = 256 * min_fit;
        r.x = (ImGui::GetIO().DisplaySize.x - r.w) / 2;
        r.y = (ImGui::GetIO().DisplaySize.y - r.h) / 2;
        SDL_SetRenderDrawColor(ren, 16, 16, 16, 255);
        SDL_SetRenderTarget(ren, NULL);
        SDL_RenderCopy(ren, tex, NULL, &r);
    }

    void BytePusher::loadROM(std::string path)
    {
        std::ifstream fin(path.c_str(), std::ios::binary | std::ios::ate);
        if(fin.fail())
        {
            std::string output = "Could not load ROM at path: " + path + "\nContinuing without a ROM...";
            Core::show_error_window(output.c_str(), parent -> getWindow() -> getSDL());
        }
        else
        {
            // Get the file size and read
            int32_t size = 0;
            size = fin.tellg();
            fin.seekg(std::ios::beg);
            fin.read(reinterpret_cast<char*>(state -> RAM), size), vm -> start();
        }
        fin.close();
    }
    
    void BytePusher::update(double dt)
    {
        // Update the input
        Core::Input* input = parent -> getWindow() -> getInput();
        for(auto i = 0; i < 0x10; i++)
            state -> keys[i] = input -> getKey(state -> keyBind[i]);

        // Update the CPU
        vm -> update(dt);
    }
};