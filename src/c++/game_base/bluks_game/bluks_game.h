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
    BluksGame();

    auto start() -> void;

    auto pause() -> void;

    auto unpause() -> void;

    auto tick() -> void;

    inline auto settings() -> GameSettings& { return m_settings; }

    inline auto map() -> Map& { return m_map; }

    inline auto current_shape() -> Shape const& { return m_current_shape; }

    inline auto next_shape() -> Shape const& { return m_next_shape; }

    inline auto tick_period() -> float { return m_tick_period; }

    inline auto paused() -> bool { return m_paused; }

   private:
    auto spawn_new_shape() -> Shape const&;

    u32 score = 0;
    float m_tick_period = 1;  // sec
    bool m_paused = false;
    Shape m_next_shape = {};
    Shape m_current_shape = {};
    Map m_map = {};
    GameSettings m_settings = {};
  };
}  // namespace bluks::game
