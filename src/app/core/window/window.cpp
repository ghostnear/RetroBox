#include "window.hpp"

namespace Core
{
    void show_error_window(const char *message, SDL_Window* window)
    {
        if(SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, window) < 0)
            std::cerr << "{E}: " << message << '\n';
    }

    namespace Rendering
    {
        using namespace Core;

        Window::Window()
        {
            // Assume everything works
            quit = false;

            // Init SDL
            if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
            {
                show_error_window("Could not initialise SDL2!", nullptr);
                exit(EXIT_FAILURE);
            }

            // Event pointer
            event = new SDL_Event();

            // Window creation
            winPtr = SDL_CreateWindow("<window_name>", SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED, 960, 540, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
            if(winPtr == nullptr)
                show_error_window("Could not create SDL2 window!", nullptr), quit = true;

            // Init SDL_Renderer
            renderer = new Renderer(this);

            // Init ImGUI
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            io = ImGui::GetIO();
            ImGui::StyleColorsDark();
            ImGui_ImplSDL2_InitForSDLRenderer(winPtr, renderer -> getSDL());
            ImGui_ImplSDLRenderer_Init(renderer -> getSDL());
        }

        Window::~Window()
        {
            ImGui_ImplSDLRenderer_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();
            SDL_DestroyWindow(winPtr);
            SDL_Quit();
        }

        Renderer* Window::getRenderer()
        {
            return renderer;
        }

        void Window::close()
        {
            quit = true;
        }

        void Window::toggleFullscreen()
        {
            SDL_SetWindowFullscreen(winPtr, !(SDL_GetWindowFlags(winPtr) & SDL_WINDOW_FULLSCREEN));
        }

        void Window::setWindowTitle(std::string name)
        {
            if(name != "")
                SDL_SetWindowTitle(winPtr, name.c_str());
        }

        void Window::pollEvents()
        {
            // Update inputs
            inputHandler.update();

            // Poll all events
            while(SDL_PollEvent(event))
            {
                ImGui_ImplSDL2_ProcessEvent(event);
                switch(event -> type)
                {
                // Quit the app
                case SDL_QUIT:
                    quit = true;
                    break;
                // Probably an input event
                default:
                    if(!ImGui::IsAnyItemFocused())
                        inputHandler.process_event(event);
                    break;
                }
            }

            // Check for special window keybinds
            // TODO: make an input bind system
            if(inputHandler.getKey((char)SDLK_F11))
                toggleFullscreen();
        }

        Core::Input* Window::getInput()
        {
            return &inputHandler;
        }

        void Window::drawStart()
        {
            // Prepare for drawing
            ImGui_ImplSDLRenderer_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
            SDL_RenderClear(renderer -> getSDL());
        }

        void Window::drawEnd()
        {
            ImGui::Render();
            ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
            SDL_RenderPresent(renderer -> getSDL());
        }
        
        bool Window::isQuit()
        {
            return quit;
        }

        SDL_Window* Window::getSDL()
        {
            return winPtr;
        }
    };
};