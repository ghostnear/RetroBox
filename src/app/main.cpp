// Libraries
#include <core.hpp>
#include <emulators.hpp>

using namespace Core;

// Main entry point
int main(int argc, char* argv[])
{
    // System variables
    Rendering::Window win;
    StateManager stateManager(&win);

    // System variables 2
    Timer deltaTimer;
    auto initState = new Emulators::CHIP8();
    stateManager.pushState((State*) initState);

    // Main app loop
    while(!win.isQuit())
    {
        // Poll app events
        win.pollEvents();

        // Update the app
        deltaTimer.update();
        stateManager.update(deltaTimer.getDelta());

        // Draw the app
        win.drawStart();
        stateManager.draw();
        win.drawEnd();
    }

    // Exit
    return EXIT_SUCCESS;
}