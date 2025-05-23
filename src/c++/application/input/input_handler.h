#pragma once

#include <chrono>
#include <functional>

#include <GLFW/glfw3.h>

namespace bluks::app::input
{
  class InputHandler
  {
   public:
    enum class Action
    {
      Up,
      Down,
      Right,
      Left,
      Pause,
      Drop,
      Exit
    };

    InputHandler(GLFWwindow* window);

    auto process_keys() -> void;
    auto bind_to_action(Action action, std::function<void()> const& callback) -> void;

   private:
    using Clock = std::chrono::steady_clock;

    struct KeyState
    {
      bool is_pressed = false;
      Clock::time_point first_pressed;
      Clock::time_point last_repeat;
    };

    GLFWwindow* m_window = nullptr;
    std::unordered_map<Action, std::vector<std::function<void()>>> m_callbacks;
    std::unordered_map<int, KeyState> m_key_states;
  };
}  // namespace bluks::app::input
