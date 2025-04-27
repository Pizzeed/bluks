#pragma once
#include <vector>
#include <game_base/shapes/block.h>

namespace bluks_game
{
  class Map
  {
   public:
    auto height() const -> int;
    auto width() const -> int;
    auto create_block(Block&& block) -> Block*;

   private:
    int const m_width = 10;
    int const m_height = 20;
    std::vector<Block> m_blocks = {};
  };
}  // namespace bluks_game
