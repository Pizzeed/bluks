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
    if(m_blocks.empty())
      return false;
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
    if(m_blocks.empty())
      return;
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
    if(m_blocks.empty())
      return;
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
    if(m_blocks.empty())
      return;
    while(move_down())
      ;
  }

  auto Shape::rotate_clockwise() -> void
  {
    if(m_blocks.empty())
      return;

    auto center = m_blocks[0]->position();
    std::vector<std::pair<int, int>> new_positions;

    for(auto& block : m_blocks) {
      int x = block->position().x;
      int y = block->position().y;

      int new_x = center.x + (y - center.y);
      int new_y = center.y - (x - center.x);

      if(new_x < 0 || new_x >= m_map->width() || new_y < 0 || new_y >= m_map->height())
        return;

      if(m_map->has_block_at(new_x, new_y) && ! is_own_block(m_blocks, new_x, new_y))
        return;

      new_positions.emplace_back(new_x, new_y);
    }

    // Apply the new positions
    for(size_t i = 0; i < m_blocks.size(); ++i) {
      m_blocks[i]->position().x = new_positions[i].first;
      m_blocks[i]->position().y = new_positions[i].second;
    }
  }

  auto Shape::rotate_counterclockwise() -> void {}
}  // namespace bluks::game
