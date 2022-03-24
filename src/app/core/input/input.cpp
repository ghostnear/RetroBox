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

    void Input::update()
    {
        for(auto i : keyStatus)
            lastKeyStatus[i.first] = i.second;
    }

    bool Input::getKey(char key)
    {
        return keyStatus[key];
    }

    bool Input::getKeyPressed(char key)
    {
        return keyStatus[key] && keyStatus[key] != lastKeyStatus[key];
    }

    bool Input::getKeyReleased(char key)
    {
        return !keyStatus[key] && keyStatus[key] != lastKeyStatus[key];
    }
};