#pragma once
#include <utils/color.h>

namespace bluks_game
{
  struct Point
  {
    int x = 0;
    int y = 0;
  };

  class Block

  {
   public:
    Block(Color color, Point const& position)
      : m_color(color)
      , m_position(position) {};

    inline auto set_position(Point const& position) -> void
    {
      m_position = position;
    }

    inline auto color() const -> Color { return m_color; }

   private:
    Color m_color = {};
    Point m_position = {};
  };
}  // namespace bluks_game
