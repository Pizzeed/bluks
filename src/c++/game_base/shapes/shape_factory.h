#pragma once
#include <game_base/map.h>
#include <game_base/shapes/block.h>

namespace bluks_game
{
  class ShapeFactory
  {
   public:
    enum class ShapeType
    {
      I,
      L,
      J,
      S,
      Z,
      T,
      B  // box
    };
    enum class RandomizerMode
    {
      Random,
      Balanced
    };

    ShapeFactory(Map* map, RandomizerMode mode = RandomizerMode::Balanced);

    auto create_shape(ShapeType type);
    auto create_random_shape(ShapeType type);

   private:
    Map* map;
  };
}  // namespace bluks_game
