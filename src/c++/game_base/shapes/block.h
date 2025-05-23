#pragma once
#include <utils/color.h>

namespace bluks::game
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
      , m_position(position)
    {}

    inline auto position() const -> Point const& { return m_position; }

    inline auto position() -> Point& { return m_position; }

    inline auto color() const -> Color const& { return m_color; }

    inline auto color() -> Color& { return m_color; }

   private:
    Color m_color = {};
    Point m_position = {};
  };
}  // namespace bluks::game
