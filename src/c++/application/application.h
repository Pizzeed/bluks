#pragma once

#include <GLFW/glfw3.h>

#include <utils/types.h>
#include <game_base/bluks_game/bluks_game.h>
#include <application/input/input_handler.h>
#include <application/graphics/shaders/shader_manager/shader_manager.h>

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
    static auto framebuffer_size_callback(
      GLFWwindow* window,
      int width,
      int height
    ) -> void;
    auto get_gl_block_vertices(bluks::game::Block const& block)
      -> std::vector<f32>;
    auto get_gl_map_background_vertices() -> std::vector<f32>;

    bluks::game::BluksGame m_game;
    std::unique_ptr<input::InputHandler> m_input_handler = nullptr;
    std::unique_ptr<graphics::shaders::ShaderManager>
      m_shader_manager = nullptr;
    GLFWwindow* m_window;

    u32 m_vao = 0;
    u32 m_vbo = 0;
    u32 m_ebo = 0;
    u32 m_window_width = 800;
    u32 m_window_height = 600;
    f32 m_map_x = .0;
    f32 m_map_y = .0;
    f32 m_actual_map_width = .0;
    f32 m_actual_map_height = .0;
  };
}  // namespace bluks::app
