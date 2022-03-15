#ifndef APP_WINDOW_HPP
#define APP_WINDOW_HPP

#include <SDL.h>
#include <iostream>

namespace Core
{
    // Show error window
    // Works even if window is not initialised
    void show_error(const char *message, SDL_Window* window);

    namespace Rendering
    {
        class Window
        {
        private:
            bool quit;
            SDL_Event* event;
            SDL_Window* winPtr;

        public:
            // Default constructor
            Window();

            // Check if is still running
            bool isQuit();

            // Poll events
            void pollEvents();

            // Get SDL_Window instance
            SDL_Window* getSDLWindow();
        };
    };
};


#endif