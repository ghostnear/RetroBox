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
    public:
        // Process an event
        void process_event(SDL_Event* event);

        // Gets key status
        bool getKey(char key);
    };
};

#endif