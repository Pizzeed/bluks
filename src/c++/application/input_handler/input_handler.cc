#include <application/input_handler/input_handler.h>

namespace bluks::app::input
{
  auto InputHandler::process_keys() -> void {}

  auto InputHandler::bind_to_action(Action const action, std::function<void()> const& callback)
    -> void
  {
    m_callbacks[action].push_back(callback);
  }

  auto InputHandler::get() -> InputHandler*
  {
    static InputHandler inst;
    return &inst;
  }
}  // namespace bluks::app::input
