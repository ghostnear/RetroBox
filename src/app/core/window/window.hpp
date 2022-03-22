#ifndef CORE_WINDOW_HPP
#define CORE_WINDOW_HPP

#include <SDL.h>
#include <imgui.h>
#include <iostream>
#include <SDL_opengl.h>
#include <../input/input.hpp>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

namespace Core
{
    // Show error window
    // Works even if window is not initialised
    void show_error_window(const char *message, SDL_Window* window);

    namespace Rendering
    {
        class Window
        {
        private:
            bool quit;
            SDL_Event* event;
            SDL_Window* winPtr;
            Core::Input inputHandler;
            SDL_GLContext gl_context;
            ImVec4 clear_color = ImVec4(0.0, 0.0, 0.0, 1.00);
            ImGuiIO io;

        public:
            // Constructor
            Window();

            // Destructor
            ~Window();

            // Sets the window title
            void setWindowTitle(std::string name);

            // Force close the window
            void close();

            // Check if is still running
            bool isQuit();

            // Get input context
            Core::Input* getInput();

            // Prepare for drawing
            void drawStart();

            // Finish drawing
            void drawEnd();

            // Poll events
            void pollEvents();

            // Get SDL_Window instance
            SDL_Window* getSDL();
        };
    };
};


#endif