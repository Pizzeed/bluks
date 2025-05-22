#pragma once
#include <utils/types.h>
#include <GLFW/glfw3.h>

namespace bluks::graphics
{
  class GraphicsHandler
  {
   public:
    GraphicsHandler();
    ~GraphicsHandler();

    static auto window() -> GLFWwindow* const;
    auto run_graphics_loop() -> void;

   private:
    auto init_graphics() -> void;
    auto cleanup() -> void;

    GLFWwindow* m_window;

    u32 m_window_width = 800;
    u32 m_window_height = 600;
  };
}  // namespace bluks::graphics
