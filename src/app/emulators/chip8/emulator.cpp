#include "header/chip8.hpp"

namespace Emulators
{
    void CHIP8::init()
    {
        parent -> getWindow() -> setWindowTitle("Owari | CHIP8");
        state = new CHIP8State();
        cpu = new CHIP8Interpreter();
    }

    void CHIP8::draw()
    {
        if(state -> debugging)
        {
            ImGui::Begin("CHIP8 Debugger");
            ImGui::Text("Performance: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            state -> draw();
            ImGui::End();
        }
    }
    
    void CHIP8::update(double dt)
    {
        cpu -> update(dt);
    }
};