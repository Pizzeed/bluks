#pragma once

#include <functional>

#include <GLFW/glfw3.h>

namespace bluks::app::input
{
  class InputHandler
  {
   public:
    enum class Action
    {
      Any,
      Up,
      Down,
      Right,
      Left,
      Pause,
      Drop,
      Hold,
      Exit
    };

    InputHandler(InputHandler const& other) = delete;
    InputHandler(InputHandler&& other) = delete;
    auto operator=(InputHandler const& other) = delete;
    auto operator=(InputHandler&& other) = delete;

    auto process_keys() -> void;
    auto bind_to_action(Action action, std::function<void()> const& callback) -> void;
    auto get() -> InputHandler*;

   private:
    InputHandler();
    std::unordered_map<Action, std::vector<std::function<void()>>> m_callbacks;
  };
}  // namespace bluks::app::input
