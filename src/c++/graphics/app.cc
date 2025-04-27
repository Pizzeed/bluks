#define GLFW_INCLUDE_VULKAN
#include <iostream>
#include <stdexcept>
#include <vector>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <graphics/app.h>

std::vector<const char*> const validation_layers = {
  "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
bool const enable_validation_layers = false;
#else
bool const enable_validation_layers = true;
#endif

static VKAPI_ATTR auto VKAPI_CALL debug_callback(
  VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
  VkDebugUtilsMessageTypeFlagsEXT messageType,
  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
  void* pUserData
) -> VkBool32
{
  std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;
  return VK_FALSE;
}

auto create_debug_utils_messenger_EXT(
  VkInstance instance,
  VkDebugUtilsMessengerCreateInfoEXT const* pCreateInfo,
  VkAllocationCallbacks const* pAllocator,
  VkDebugUtilsMessengerEXT* pDebugMessenger
) -> VkResult
{
  auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
    vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT")
  );
  if(not func)
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
}

void destroy_debug_utils_messenger_EXT(
  VkInstance instance,
  VkDebugUtilsMessengerEXT debugMessenger,
  VkAllocationCallbacks const* pAllocator
)
{
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT
  )vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  if(func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }
}

auto populate_debug_messenger_create_info(
  VkDebugUtilsMessengerCreateInfoEXT& createInfo
) -> void
{
  createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  createInfo.pfnUserCallback = debug_callback;
}

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

    if(enable_validation_layers && !check_validation_layer_support())
      throw std::runtime_error("Requested validation layers not available!");

    create_vk_instance();
    setup_debug_messenger();
  }

  auto BluksApplication::create_vk_instance() -> void
  {
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

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo {};
    if(enable_validation_layers) {
      createInfo.enabledLayerCount = static_cast<uint32_t>(
        validation_layers.size()
      );
      createInfo.ppEnabledLayerNames = validation_layers.data();

      populate_debug_messenger_create_info(debugCreateInfo);
      createInfo.pNext = static_cast<VkDebugUtilsMessengerCreateInfoEXT*>(
        &debugCreateInfo
      );
    }
    else {
      createInfo.enabledLayerCount = 0;

      createInfo.pNext = nullptr;
    }

    u32 glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    auto extensions = get_required_extensions();
    createInfo.enabledExtensionCount = static_cast<u32>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    if(vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
      throw std::runtime_error("Failed to create Vulkan instance!");
    }
  }

  auto BluksApplication::setup_debug_messenger() -> void
  {
    if(!enable_validation_layers)
      return;
    VkDebugUtilsMessengerCreateInfoEXT createInfo {};
    populate_debug_messenger_create_info(createInfo);
    if(create_debug_utils_messenger_EXT(
         m_instance,
         &createInfo,
         nullptr,
         &debug_messenger
       ) != VK_SUCCESS) {
      throw std::runtime_error("Failed to set up debug messenger!");
    }
  }

  auto BluksApplication::run_gui_loop() -> void
  {
    while(!glfwWindowShouldClose(m_window))
      glfwPollEvents();
  }

  auto BluksApplication::cleanup() -> void
  {
    if(enable_validation_layers)
      destroy_debug_utils_messenger_EXT(m_instance, debug_messenger, nullptr);
    vkDestroyInstance(m_instance, nullptr);
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

  auto BluksApplication::check_validation_layer_support() -> bool const
  {
    u32 layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

    auto available_layers = std::vector<VkLayerProperties>(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

    for(auto ln : validation_layers) {
      bool layer_found = false;

      for(auto const& lp : available_layers) {
        if(strcmp(ln, lp.layerName) == 0) {
          layer_found = true;
          break;
        }
      }

      if(!layer_found)
        return false;
    }

    return true;
  }

  auto BluksApplication::get_required_extensions() -> std::vector<const char*>
  {
    u32 glfwExtensionCount = 0;
    auto** glfwExtensions = glfwGetRequiredInstanceExtensions(
      &glfwExtensionCount
    );

    auto extensions = std::vector<const char*>(
      glfwExtensions,
      glfwExtensions + glfwExtensionCount
    );

    if(enable_validation_layers)
      extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    return extensions;
  }
}  // namespace bluks_gui
