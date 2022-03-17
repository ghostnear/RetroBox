// Libraries
#include <SDL.h>
#include <core.hpp>

using namespace Core;

// Main entry point
int main(int argc, char* argv[])
{
    // Build window
    Rendering::Window* win = new Rendering::Window();

    // Main app loop
    while(!win -> isQuit())
    {
        // Poll window events
        win -> pollEvents();
    }

    // Exit
    delete win;
    return EXIT_SUCCESS;
}