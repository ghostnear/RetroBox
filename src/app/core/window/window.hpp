#ifndef CORE_WINDOW_HPP
#define CORE_WINDOW_HPP

#include <SDL.h>
#include <imgui.h>
#include <iostream>
#include "../input/input.hpp"
#include "renderer/renderer.hpp"
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_sdlrenderer.h>

namespace Core
{
    // Show error window
    // Works even if window is not initialised
    void show_error_window(const char *message, SDL_Window* window);

    namespace Rendering
    {
        class Renderer;

        class Window
        {
        private:
            bool quit;
            SDL_Event* event;
            SDL_Window* winPtr;
            Renderer* renderer;
            std::pair<int, int> lastFullscreen;
            bool fullscreen = false;
            Core::Input inputHandler;
            ImVec4 clear_color = ImVec4(0.0, 0.0, 0.0, 1.00);
            ImGuiIO io;

        public:
            // Constructor
            Window();

            // Destructor
            ~Window();

            // Toggles fullscreen
            void toggleFullscreen();

            // Toggles fullscreen (non-exclusive)
            void toggleFullscreenBorderless();

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

            // Get the renderer
            Renderer* getRenderer();

            // Get SDL_Window instance
            SDL_Window* getSDL();
        };
    };
};


#endif