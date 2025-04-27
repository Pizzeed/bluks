#pragma once
#include <vector>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <utils/types.h>

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
    auto create_vk_instance() -> void;
    auto run_gui_loop() -> void;
    auto cleanup() -> void;
    auto check_validation_layer_support() -> bool const;
    auto get_required_extensions() -> std::vector<const char*>;
    auto setup_debug_messenger() -> void;

    GLFWwindow* m_window;
    VkInstance m_instance;
    VkDebugUtilsMessengerEXT debug_messenger;
    u32 m_window_width = 800;
    u32 m_window_height = 600;
  };
}  // namespace bluks_gui
