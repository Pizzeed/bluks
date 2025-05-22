#pragma once
#include <game_base/shapes/block.h>

#include <vector>

namespace bluks::game {
class Shape {
  auto move_down() -> void;
  auto move_left() -> void;
  auto move_right() -> void;
  auto rotate_clockwise() -> void;
  auto rotate_counterclockwise() -> void;

 private:
  std::vector<Block*> m_blocks;
};
}  // namespace bluks::game
