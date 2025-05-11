#pragma once
#include <utils/types.h>
#include <GLFW/glfw3.h>

namespace bluks_gui
{
  class GraphicsHandler
  {
   public:
    GraphicsHandler();
    
    auto run() -> void;
    static auto window() -> GLFWwindow* const;

   private:
    
    auto init_gui() -> void;
    auto run_gui_loop() -> void;
    auto cleanup() -> void;

    GLFWwindow* m_window;

    u32 m_window_width = 800;
    u32 m_window_height = 600;
  };
}  // namespace bluks_gui
