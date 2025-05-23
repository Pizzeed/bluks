#include <application/input/input_handler.h>

namespace bluks::app::input
{
  using Action = InputHandler::Action;
  static std::unordered_map<int, Action> const keybinds =
    {{GLFW_KEY_W, Action::Up},
     {GLFW_KEY_A, Action::Left},
     {GLFW_KEY_S, Action::Down},
     {GLFW_KEY_D, Action::Right},
     {GLFW_KEY_UP, Action::Up},
     {GLFW_KEY_LEFT, Action::Left},
     {GLFW_KEY_DOWN, Action::Down},
     {GLFW_KEY_RIGHT, Action::Right},
     {GLFW_KEY_P, Action::Pause},
     {GLFW_KEY_ESCAPE, Action::Exit},
     {GLFW_KEY_SPACE, Action::Drop}};

  InputHandler::InputHandler(GLFWwindow* window)
    : m_callbacks()
    , m_window(window)
  {}

  auto InputHandler::process_keys() -> void
  {
    for(auto const& i : keybinds)
      if(glfwGetKey(m_window, i.first) == GLFW_PRESS)
        for(auto const& cb : m_callbacks[i.second])
          cb();
  }

  auto InputHandler::bind_to_action(Action const action, std::function<void()> const& callback)
    -> void
  {
    m_callbacks[action].push_back(callback);
  }
}  // namespace bluks::app::input
