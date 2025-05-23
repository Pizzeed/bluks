#pragma once

#include <game_base/shapes/block.h>
#include <game_base/shapes/shape.h>

namespace bluks::game
{
  auto Shape::move_down() -> void
  {
    for(auto const& block : m_blocks)
      --block->position().y;
  }

  auto Shape::move_left() -> void
  {
    for(auto const& block : m_blocks)
      --block->position().x;
  }

  auto Shape::move_right() -> void
  {
    for(auto const& block : m_blocks)
      ++block->position().x;
  }

  auto Shape::drop() -> void {}

  auto Shape::rotate_clockwise() -> void {}

  auto Shape::rotate_counterclockwise() -> void {}
}  // namespace bluks::game
