#pragma once
#include <game_base/shapes/block.h>

#include <memory>
#include <vector>

namespace bluks::game
{
  class Map
  {
   public:
    auto height() const -> int;
    auto width() const -> int;
    auto create_block(Block&& block) -> std::shared_ptr<Block>;
    auto has_block_at(int x, int y) -> bool;

    inline auto blocks() const -> std::vector<std::shared_ptr<Block>> const& { return m_blocks; }

    inline auto blocks() -> std::vector<std::shared_ptr<Block>>& { return m_blocks; }

   private:
    int const m_width = 10;
    int const m_height = 20;
    std::vector<std::shared_ptr<Block>> m_blocks = {};
  };
}  // namespace bluks::game
