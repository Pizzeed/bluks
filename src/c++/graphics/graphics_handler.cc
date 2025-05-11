
#define GLFW_EXPOSE_NATIVE_WAYLAND

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <graphics/graphics_handler.h>

namespace bluks_gui{
    
    auto GraphicsHandler::init_gui() -> void {};
    auto GraphicsHandler::run_gui_loop() -> void {};
    auto GraphicsHandler::cleanup() -> void {};
}  // namespace bluks_gui
