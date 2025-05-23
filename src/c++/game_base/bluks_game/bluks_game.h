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

    auto tick() -> void;

    inline auto settings() -> GameSettings& { return m_settings; }

    inline auto map() -> Map& { return m_map; }

    inline auto current_shape() -> Shape const& { return m_current_shape; }

    inline auto next_shape() -> Shape const& { return m_next_shape; }

   private:
    Shape m_next_shape = {};
    Shape m_current_shape = {};
    Map m_map = {};
    GameSettings m_settings = {};
  };
}  // namespace bluks::game
