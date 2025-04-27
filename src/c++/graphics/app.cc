#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <graphics/app.h>

namespace bluks_gui
{
  auto BluksApplication::run() -> void
  {
    init_gui();
    run_gui_loop();
    cleanup();
  }

  auto BluksApplication::init_gui() -> void
  {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
  }

  auto BluksApplication::run_gui_loop() -> void {};

  auto BluksApplication::cleanup() -> void {};

  auto BluksApplication::application() -> BluksApplication*
  {
    static BluksApplication app;
    return &app;
  }

  auto BluksApplication::window() -> GLFWwindow* const
  {
    return application()->m_window;
  }
}  // namespace bluks_gui
