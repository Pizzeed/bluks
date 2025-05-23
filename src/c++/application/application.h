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
    auto run_graphics_loop() -> void;

   private:
    Application();
    auto init_graphics() -> void;
    auto cleanup() -> void;
    static auto framebuffer_size_callback(GLFWwindow* window, int width, int height) -> void;
    auto get_gl_block_vertices(bluks::game::Block const& block) -> std::vector<float>;
    auto get_gl_map_background_vertices() -> std::vector<float>;

    bluks::game::BluksGame m_game;
    std::unique_ptr<input::InputHandler> m_input_handler = nullptr;
    GLFWwindow* m_window;

    u32 m_window_width = 800;
    u32 m_window_height = 600;
    float m_map_x = .0;
    float m_map_y = .0;
    float m_actual_map_width = .0;
    float m_actual_map_height = .0;

    u32 shaderProgram;
  };
}  // namespace bluks::app
