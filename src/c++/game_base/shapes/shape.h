#pragma once
#include <game_base/shapes/block.h>

#include <vector>

namespace bluks::game
{
  class Shape
  {
   public:
    auto move_down() -> void;
    auto move_left() -> void;
    auto move_right() -> void;
    auto drop() -> void;
    auto rotate_clockwise() -> void;
    auto rotate_counterclockwise() -> void;

    inline auto blocks() -> std::vector<Block*>& { return m_blocks; }

    inline auto blocks() const -> std::vector<Block*> const& { return m_blocks; }

   private:
    std::vector<Block*> m_blocks;
  };
}  // namespace bluks::game
