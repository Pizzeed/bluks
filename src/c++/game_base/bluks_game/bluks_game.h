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

    auto game_over() -> void;

    auto pause() -> void;

    auto unpause() -> void;

    auto tick() -> void;

    inline auto settings() -> GameSettings& { return m_settings; }

    inline auto map() -> Map& { return m_map; }

    inline auto current_shape() -> Shape& { return m_current_shape; }

    inline auto tick_period() -> float { return m_tick_period; }

    inline auto paused() -> bool { return m_paused; }

    inline auto ongoing() -> bool { return m_ongoing; }

    auto spawn_new_shape() -> void;

   private:
    u32 m_score = 0;
    float m_tick_period = 1;  // sec
    bool m_paused = false;
    bool m_ongoing = false;
    Shape m_current_shape = {&m_map};
    Map m_map = {};
    GameSettings m_settings = {};
  };
}  // namespace bluks::game
