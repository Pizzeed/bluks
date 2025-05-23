#pragma once

#include <GLFW/glfw3.h>

#include <utils/types.h>
#include <game_base/bluks_game/bluks_game.h>
#include <application/input/input_handler.h>

namespace bluks::app
{
  class Application
  {
   public:
    Application(Application const&) = delete;
    Application(Application&&) = delete;
    auto operator=(Application const&) = delete;
    auto operator=(Application&&) = delete;
    ~Application();

    static auto get() -> Application*;
    auto window() -> GLFWwindow* const;
    auto input_handler() -> input::InputHandler const&;
    auto run_graphics_loop() -> void;

   private:
    Application();
    auto init_graphics() -> void;
    auto cleanup() -> void;

    bluks::game::BluksGame m_game;
    input::InputHandler m_input_handler;
    GLFWwindow* m_window;

    u32 m_window_width = 800;
    u32 m_window_height = 600;

    u32 shaderProgram;
  };
}  // namespace bluks::app
