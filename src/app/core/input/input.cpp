#include "input.hpp"

namespace Core
{
    void Input::process_event(SDL_Event* event)
    {
        switch(event -> type)
        {
        case SDL_KEYDOWN:
            keyStatus[event -> key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            keyStatus[event -> key.keysym.sym] = false;
            break;
        }
    }

    bool Input::getKey(char key)
    {
        return keyStatus[key];
    }
};