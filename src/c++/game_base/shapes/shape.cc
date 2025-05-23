#include <iostream>

#include <game_base/shapes/block.h>
#include <game_base/shapes/shape.h>
#include <game_base/map/map.h>

namespace bluks::game
{
  namespace
  {
    auto is_own_block(std::vector<std::shared_ptr<Block>>& blocks, int x, int y) -> bool
    {
      for(auto b : blocks)
        if(b->position().x == x && b->position().y == y)
          return true;
      return false;
    }
  }  // namespace

  auto Shape::move_down() -> bool
  {
    for(auto block : m_blocks) {
      int x = block->position().x;
      int y = block->position().y;

      if(y == 0) {
        return false;
      }

      if(m_map->has_block_at(x, y - 1) && ! is_own_block(m_blocks, x, y - 1))
        return false;
    }
    for(auto block : m_blocks) {
      --block->position().y;
    }

    return true;
  }

  auto Shape::move_left() -> void
  {
    for(auto block : m_blocks) {
      int x = block->position().x;
      int y = block->position().y;

      if(x == 0)
        return;

      if(m_map->has_block_at(x - 1, y) && ! is_own_block(m_blocks, x - 1, y)) {
        return;
      }
    }

    for(auto block : m_blocks)
      --block->position().x;
  }

  auto Shape::move_right() -> void
  {
    for(auto block : m_blocks) {
      int x = block->position().x;
      int y = block->position().y;

      if(x == m_map->width() - 1)
        return;

      if(m_map->has_block_at(x + 1, y) && ! is_own_block(m_blocks, x + 1, y)) {
        return;
      }
    }

    for(auto block : m_blocks)
      ++block->position().x;
  }

  auto Shape::drop() -> void
  {
    while(move_down())
      ;
  }

  auto Shape::rotate_clockwise() -> void {}

  auto Shape::rotate_counterclockwise() -> void {}
}  // namespace bluks::game
