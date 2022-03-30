#include "boot.hpp"

namespace States
{
    void Boot::init()
    {
        parent -> getWindow() -> setWindowTitle(APP_NAME + " | Loading...");
    }

    void Boot::draw()
    {

    }

    void Boot::update(double dt)
    {
        
    }
}