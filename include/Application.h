/*
    file: Application.h
    written by Elias Geiger
*/

#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_joystick.h>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <iostream>
#include <vector>
#include <memory>

// compile options
// #define _USE_FULLSCREEN
// #define _USE_ADAPTIVE_SYNC

namespace Core
{
    const int window_width = 1280;
    const int window_height = 720;
    const std::string app_name = "Steamdeck Demo App";
    const std::string app_version = "1.0.0";
    const std::string app_identifier = "";
    const uint32_t min_frame_time_ms = 2;

    struct PerformanceStats
    {
        float average_frametime = 0.0f;
        float average_fps = 0.0f;
    };

    struct AnalogJoystickState
    {
        int x_axis_val = 0;
        int y_axis_val = 0;
        bool stick_pressed = false;
    };

    class Application
    {
    public:
        Application();
        virtual ~Application();
        Application(const Application &other) = delete;
        Application &operator=(const Application &) = delete;

        bool Init();
        void Run();

        void AddLaunchArgument(const std::string &arg);

    private:
        bool InitGui();
        const SDL_DisplayMode *GetFullscreenMode() const;
        bool InitGamepad();
        void CheckForButtonMappings();

        void Update();
        void DrawGui();
        void Render();

    private:
        SDL_Window *m_window;
        SDL_DisplayID m_displayId;
        SDL_Renderer *m_renderer;
        SDL_Gamepad *m_gamepad;

        bool m_running;

        AnalogJoystickState m_left_stick_state = {};
        AnalogJoystickState m_right_stick_state = {};
        PerformanceStats m_perf_stats = {};
        std::vector<std::string> m_launch_args = {};
    };
}
