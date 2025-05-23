#include <game_base/map/map.h>
#include <game_base/shapes/block.h>

#include <vector>

namespace bluks::game
{
  auto Map::height() const -> int { return m_height; }

  auto Map::width() const -> int { return m_width; }

  auto Map::create_block(Block&& block) -> std::shared_ptr<Block>
  {
    for(auto const& ex_blk : m_blocks)
      if(ex_blk->position() == block.position())
        return nullptr;
    m_blocks.emplace_back(std::make_shared<Block>(block));

    return m_blocks.back();
  }

  auto Map::has_block_at(int x, int y) -> bool
  {
    for(auto const& block : m_blocks)
      if(block->position().x == x && block->position().y == y)
        return true;
    return false;
  }
}  // namespace bluks::game
