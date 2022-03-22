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

            // Decide GL+GLSL versions
        #if defined(IMGUI_IMPL_OPENGL_ES2)
            // GL ES 2.0 + GLSL 100
            const char* glsl_version = "#version 100";
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        #elif defined(__APPLE__)
            // GL 3.2 Core + GLSL 150
            const char* glsl_version = "#version 150";
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        #else
            // GL 3.0 + GLSL 130
            const char* glsl_version = "#version 130";
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        #endif

            // More SDL GL
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

            // Window creation
            winPtr = SDL_CreateWindow("<window_name>", SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED, 960, 540, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
            if(winPtr == nullptr)
                show_error_window("Could not create window!", nullptr), quit = true;
            
            // SDLGL for Imgui
            gl_context = SDL_GL_CreateContext(winPtr);
            SDL_GL_MakeCurrent(winPtr, gl_context);
            SDL_GL_SetSwapInterval(1); // enable vsync

            // Init ImGUI
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            io = ImGui::GetIO();
            ImGui::StyleColorsDark();
            ImGui_ImplSDL2_InitForOpenGL(winPtr, gl_context);
            ImGui_ImplOpenGL3_Init(glsl_version);
        }

        Window::~Window()
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();
            SDL_GL_DeleteContext(gl_context);
            SDL_DestroyWindow(winPtr);
            SDL_Quit();
        }

        void Window::close()
        {
            quit = true;
        }

        void Window::setWindowTitle(std::string name)
        {
            if(name != "")
                SDL_SetWindowTitle(winPtr, name.c_str());
        }

        void Window::pollEvents()
        {
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
                    inputHandler.process_event(event);
                    break;
                }
            }
        }

        Core::Input* Window::getInput()
        {
            return &inputHandler;
        }

        void Window::drawStart()
        {
            // Prepare for drawing
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
        }

        void Window::drawEnd()
        {
            ImGui::Render();
            glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            SDL_GL_SwapWindow(winPtr);
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