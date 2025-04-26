#pragma once
#include <vector>
#include <game_base/block.h>

namespace bluks_game
{
  class Map
  {
   public:
    auto height() const -> int {};
    auto width() const -> int;

   private:
    int const m_width = 10;
    int const m_height = 10;
  };
}  // namespace bluks_game
