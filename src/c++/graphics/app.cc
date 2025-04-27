#define GLFW_INCLUDE_VULKAN
#include <stdexcept>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <graphics/app.h>

namespace bluks_gui
{
  BluksApplication::BluksApplication() {}

  auto BluksApplication::run() -> void
  {
    init_gui();
    run_gui_loop();
    cleanup();
  }

  auto BluksApplication::init_gui() -> void
  {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_window = glfwCreateWindow(
      m_window_width,
      m_window_height,
      "Bluks",
      nullptr,
      nullptr
    );

    VkApplicationInfo appInfo {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Bluks";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    if(vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
      throw std::runtime_error("Failed to create Vulkan instance!");
    }
  }

  auto BluksApplication::run_gui_loop() -> void
  {
    while(!glfwWindowShouldClose(m_window))
      glfwPollEvents();
  }

  auto BluksApplication::cleanup() -> void
  {
    glfwDestroyWindow(m_window);

    glfwTerminate();
  }

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
