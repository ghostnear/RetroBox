// Libraries
#include <SDL.h>
#include <window.hpp>

using namespace Core;

// Main entry point
int main(int argc, char* argv[])
{
    // Init SDL
    int SDL_result = SDL_Init(SDL_INIT_EVERYTHING);

    // Build window
    Rendering::Window* win = new Rendering::Window();
    if(SDL_result < 0)
    {
        show_error("Could not init SDL2!", nullptr);
        exit(EXIT_FAILURE);
    }

    while(!win -> isQuit())
    {
        // Poll window events
        win -> pollEvents();
    }

    // Exit
    SDL_Quit();
    return EXIT_SUCCESS;
}