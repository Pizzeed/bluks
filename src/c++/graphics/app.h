#pragma once

#include <GLFW/glfw3.h>

namespace bluks_gui
{
  class BluksApplication
  {
   public:
    auto run() -> void;

    BluksApplication(BluksApplication const& other) = delete;
    BluksApplication(BluksApplication&& other) = delete;
    auto operator=(BluksApplication const& other) = delete;
    auto operator=(BluksApplication&& other) = delete;

    static auto application() -> BluksApplication*;
    static auto window() -> GLFWwindow* const;

   private:
    BluksApplication();

    auto init_gui() -> void;

    auto run_gui_loop() -> void;

    auto cleanup() -> void;

    GLFWwindow* m_window;
  };
}  // namespace bluks_gui
