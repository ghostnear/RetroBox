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

    // Test state
    auto initState = new Emulators::CHIP8();
    stateManager.pushState((State*) initState);
    initState -> loadROM("./roms/IBM Logo.ch8");

    // Main app loop
    while(!win.isQuit())
    {
        // Poll app events
        win.pollEvents();

        // Update the app
        stateManager.update(ImGui::GetIO().Framerate);

        // Draw the app
        win.drawStart();
        stateManager.draw();
        win.drawEnd();

        // Arbitrary value, might need tweaks.
        SDL_Delay(5);
    }

    // Exit
    return EXIT_SUCCESS;
}