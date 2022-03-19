#include "statemanager.hpp"

namespace Core
{
    StateManager::StateManager(Rendering::Window* window)
    {
        // Save the window pointer
        win = window;
    }

    Rendering::Window* StateManager::getWindow()
    {
        return win;
    }

    void StateManager::pushState(State* state)
    {
        state -> setParent(this);
        state -> init();
        stateQueue.push_back(state);
    }

    void StateManager::update(double dt)
    {
        // Update all states
        for(auto i : stateQueue)
            i -> update(dt);
    }

    void StateManager::draw()
    {
        // Draw all states
        for(auto i : stateQueue)
            i -> draw();
    }
};