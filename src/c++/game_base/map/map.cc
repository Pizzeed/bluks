#include <game_base/map/map.h>
#include <game_base/shapes/block.h>

#include <vector>

namespace bluks::game {
auto Map::height() const -> int { return m_height; }

auto Map::width() const -> int { return m_width; }

auto Map::create_block(Block&& block) -> Block* {
  return &m_blocks.emplace_back(std::move(block));
}
}  // namespace bluks::game
