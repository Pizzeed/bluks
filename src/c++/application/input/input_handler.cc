#include <GLFW/glfw3.h>
#include <application/input/input_handler.h>
#include <unordered_map>
#include <functional>
#include <chrono>

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
    , m_key_states()
  {}

  auto InputHandler::process_keys() -> void
  {
    auto now = Clock::now();
    for(auto const& [key, action] : keybinds) {
      int state = glfwGetKey(m_window, key);
      bool is_down = (state == GLFW_PRESS);
      auto& ks = m_key_states[key];

      if(is_down) {
        if(! ks.is_pressed) {
          // First time key is pressed
          ks.is_pressed = true;
          ks.first_pressed = now;
          ks.last_repeat = now;
          for(auto const& cb : m_callbacks[action])
            cb();
        }
        else {
          auto time_held = std::chrono::duration_cast<std::chrono::milliseconds>(
                             now - ks.first_pressed
          )
                             .count();
          auto time_since_last = std::chrono::duration_cast<std::chrono::milliseconds>(
                                   now - ks.last_repeat
          )
                                   .count();

          if(time_held > 1'000 && time_since_last >= 250) {
            ks.last_repeat = now;
            for(auto const& cb : m_callbacks[action])
              cb();
          }
        }
      }
      else {
        ks.is_pressed = false;  // reset when key is released
      }
    }
  }

  auto InputHandler::bind_to_action(Action const action, std::function<void()> const& callback)
    -> void
  {
    m_callbacks[action].push_back(callback);
  }
}  // namespace bluks::app::input
