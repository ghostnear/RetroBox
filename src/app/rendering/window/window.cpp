#include "window.hpp"

namespace Core
{
    void show_error(const char *message, SDL_Window* window)
    {
        if(SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, window) < 0)
            std::cerr << "{E}: " << message << '\n';
    }

    namespace Rendering
    {
        using namespace Core;

        Window::Window()
        {
            // Assume everything works
            quit = false;

            // Event pointer
            event = new SDL_Event();

            // Window creation
            winPtr = SDL_CreateWindow("<window_name>", SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED, 960, 540, SDL_WINDOW_SHOWN);

            if(winPtr == nullptr)
                show_error("Could not create window!", nullptr), quit = true;

        }

        void Window::pollEvents()
        {
            // Poll all events
            while(SDL_PollEvent(event))
            {
                switch(event -> type)
                {
                // Quit the app
                case SDL_QUIT:
                    quit = true;
                    break;
                }  
            }
        }
        
        bool Window::isQuit()
        {
            return quit;
        }

        SDL_Window* Window::getSDLWindow()
        {
            return winPtr;
        }
    };
};