#ifndef CORE_RENDERER_HPP
#define CORE_RENDERER_HPP

#include <SDL.h>
#include "../window.hpp"

namespace Core
{
    namespace Rendering
    {
        class Window;

        class Renderer
        {
        private:
            SDL_Renderer* ren = nullptr;
        public:
            Renderer(Window* win);

            SDL_Renderer* getSDL();
        };
    };
};

#endif