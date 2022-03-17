#ifndef CORE_STATEMANAGER_HPP
#define CORE_STATEMANAGER_HPP

#include "state.hpp"
#include <queue>

namespace Core
{
    class StateManager
    {
    private:
        Rendering::Window* win;
        std::deque<State*> stateQueue;

    public:
        // Constructor
        StateManager(Rendering::Window* win);

        // Getters
        Rendering::Window* getWindow();

        // Main functions
        void pushState(State* state);
        void update(double dt);
        void draw();
    };
};

#endif