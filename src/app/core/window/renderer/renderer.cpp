#include "renderer.hpp"

namespace Core
{
    namespace Rendering
    {
        Renderer::Renderer(Window* win)
        {
            // Create renderer and throw an error if it fails
            ren = SDL_CreateRenderer(win -> getSDL(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(ren == nullptr)
                show_error_window("Could not create SDL2 renderer!", nullptr), win -> close();
        }

        SDL_Renderer* Renderer::getSDL()
        {
            return ren;
        }
    };
};