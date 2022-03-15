// SDL stuff
#include <SDL.h>

// C++ libs
#include <iostream>

// Show error in message box
static void show_error(const char *message, SDL_Window *window)
{
    if(SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, window) < 0)
        std::cerr << "{E}: " << message << '\n';
}

// Main entry point
int SDL_main(int argc, char* argv[])
{
    // Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        show_error("Could not init SDL2!", nullptr);
        exit(EXIT_FAILURE);
    }

    // Test stuff
    show_error("Test", nullptr);

    // Exit
    SDL_Quit();
    return EXIT_SUCCESS;
}