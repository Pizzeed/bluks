#pragma once
#include <vector>
#include <game_base/shapes/block.h>

namespace bluks_game
{
  class Shape
  {
    auto move_down() -> void;
    auto move_left() -> void;
    auto move_right() -> void;
    auto rotate_clockwise() -> void;
    auto rotate_counterclockwise() -> void;

   private:
    std::vector<Block*> m_blocks;
  };
}  // namespace bluks_game
