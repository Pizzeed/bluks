#include <iostream>

#include <graphics/glad/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/graphics_handler.h>

namespace bluks::graphics
{
  auto framebuffer_size_callback(GLFWwindow* window, int width, int height) -> void
  {
    glViewport(0, 0, width, height);
  }

  GraphicsHandler::GraphicsHandler() { init_graphics(); }

  GraphicsHandler::~GraphicsHandler() { cleanup(); }

  auto GraphicsHandler::init_graphics() -> void
  {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(m_window_width, m_window_height, "Bluks", NULL, NULL);
    if(not m_window) {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return;
    }
    glfwMakeContextCurrent(m_window);
    if(! gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      glfwTerminate();
      return;
    }
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
  }

  auto GraphicsHandler::run_graphics_loop() -> void
  {
    while(! glfwWindowShouldClose(m_window)) {
      glfwSwapBuffers(m_window);
      glfwPollEvents();
    }
  }

  auto GraphicsHandler::cleanup() -> void { glfwTerminate(); }
}  // namespace bluks::graphics
