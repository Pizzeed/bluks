#pragma once
#include <utils/color.h>

namespace bluks::game
{
  struct Point
  {
    int x = 0;
    int y = 0;

    bool operator==(Point const& other) const
    {
      return x == other.x && y == other.y;
    }

    bool operator!=(Point const& other) const { return ! (*this == other); }
  };

  class Block
  {
   public:
    Block(utils::Color color, Point const& position)
      : m_color(color)
      , m_position(position)
    {}

    inline auto position() const -> Point const& { return m_position; }

    inline auto position() -> Point& { return m_position; }

    inline auto color() const -> utils::Color const& { return m_color; }

    inline auto color() -> utils::Color& { return m_color; }

   private:
    utils::Color m_color = {};
    Point m_position = {};
  };
}  // namespace bluks::game
