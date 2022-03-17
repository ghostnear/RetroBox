// Libraries
#include <SDL.h>
#include <iostream>
#include <core.hpp>

using namespace Core;

// Main entry point
int main(int argc, char* argv[])
{
    // System variables
    Rendering::Window win;
    StateManager stateManager(&win);
    Timer deltaTimer;

    // Main app loop
    while(!win.isQuit())
    {
        // Poll window events
        win.pollEvents();

        // Update the timer
        deltaTimer.update();

        // Update the app
        stateManager.update(deltaTimer.getDelta());

        // Draw the app
        stateManager.draw();
    }

    // Exit
    return EXIT_SUCCESS;
}