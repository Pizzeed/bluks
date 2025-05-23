#pragma once
#include <game_base/shapes/block.h>
#include <game_base/shapes/shape.h>

namespace bluks::game
{
  class Map;

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
      Chaotic,
      Random,
      Balanced
    };

    ShapeFactory(Map* map, RandomizerMode mode = RandomizerMode::Balanced);

    auto create_random_shape(bool& result) -> Shape;

   private:
    auto create_shape(ShapeType type, bool& result) -> Shape;
    auto create_i(bool& result) -> Shape;
    auto create_l(bool& result) -> Shape;
    auto create_j(bool& result) -> Shape;
    auto create_s(bool& result) -> Shape;
    auto create_z(bool& result) -> Shape;
    auto create_t(bool& result) -> Shape;
    auto create_b(bool& result) -> Shape;

    Map* m_map;
    RandomizerMode m_mode;
  };
}  // namespace bluks::game
