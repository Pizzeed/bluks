#pragma once
#include <vector>

#include <game_base/shapes/block.h>
#include <game_base/map/map.h>

namespace bluks::game
{
  class Shape
  {
   public:
    Shape(Map* map)
      : m_map(map)
    {}

    auto move_down() -> bool;
    auto move_left() -> void;
    auto move_right() -> void;
    auto drop() -> void;
    auto rotate_clockwise() -> void;
    auto rotate_counterclockwise() -> void;

    inline auto blocks() -> std::vector<std::shared_ptr<Block>>& { return m_blocks; }

    inline auto blocks() const -> std::vector<std::shared_ptr<Block>> const& { return m_blocks; }

   private:
    std::vector<std::shared_ptr<Block>> m_blocks;
    Map* m_map;
  };
}  // namespace bluks::game
