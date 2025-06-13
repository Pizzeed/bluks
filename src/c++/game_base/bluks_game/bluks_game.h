#pragma once

#include <game_base/shapes/shape.h>
#include <game_base/map/map.h>

namespace bluks::game
{
  struct GameSettings
  {};

  class BluksGame
  {
   public:
    enum class GameState
    {
      NotStarted,
      Ongoing,
      Paused,
      GameOver
    };

    BluksGame();

    auto start() -> void;

    auto game_over() -> void;

    auto pause() -> void;

    auto unpause() -> void;

    auto tick() -> void;

    inline auto settings() -> GameSettings& { return m_settings; }

    inline auto map() -> Map& { return m_map; }

    inline auto current_shape() -> Shape& { return m_current_shape; }

    inline auto tick_period() const -> f32 { return m_tick_period; }

    inline auto state() const -> GameState { return m_state; }

    inline auto score() const -> u32 { return m_score; }

    auto spawn_new_shape() -> void;

    auto check_lines() -> void;

   private:
    u32 m_score = 0;
    GameState m_state = GameState::NotStarted;
    f32 m_tick_period = 1;  // sec
    Shape m_current_shape = {&m_map};
    Map m_map = {};
    GameSettings m_settings = {};
  };
}  // namespace bluks::game
