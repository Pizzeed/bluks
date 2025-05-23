#pragma once
#include <game_base/shapes/block.h>

#include <vector>

namespace bluks::game
{
  class Map
  {
   public:
    auto height() const -> int;
    auto width() const -> int;
    auto create_block(Block&& block) -> Block*;

    inline auto blocks() -> std::vector<Block> const& { return m_blocks; }

   private:
    int const m_width = 10;
    int const m_height = 20;
    std::vector<Block> m_blocks = {};
  };
}  // namespace bluks::game
