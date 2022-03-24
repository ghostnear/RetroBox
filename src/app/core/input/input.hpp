#ifndef CORE_INPUT_HPP
#define CORE_INPUT_HPP

#include <map>
#include <SDL.h>
#include <iostream>

namespace Core
{
    class Input
    {
    public:
        std::map<char, bool> keyStatus;
        std::map<char, bool> lastKeyStatus;
    public:
        // Process an event
        void process_event(SDL_Event* event);

        // Update
        void update();

        // Gets key status
        bool getKey(char key);
        bool getKeyReleased(char key);
        bool getKeyPressed(char key);
    };
};

#endif