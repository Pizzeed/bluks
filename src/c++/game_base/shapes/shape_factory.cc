#include <random>
#include <stdexcept>

#include <game_base/map/map.h>
#include <game_base/shapes/block.h>
#include <game_base/shapes/shape_factory.h>

namespace bluks::game
{
  ShapeFactory::ShapeFactory(Map* map, RandomizerMode mode)
    : m_map(map)
    , m_mode(mode)
  {
    if(not map)
      throw std::runtime_error("ShapeFactory constructor: map is invalid");
    if(mode != RandomizerMode::Chaotic)
      mode = RandomizerMode::Chaotic;  // TODO
  }

  auto ShapeFactory::create_random_shape(bool& result) -> Shape
  {
    static std::mt19937 rng(std::random_device {}());
    static std::uniform_int_distribution<int> gen(0, 6);

    switch(m_mode) {
      case RandomizerMode::Balanced:  // Todo
      case RandomizerMode::Random:    // Todo
      case RandomizerMode::Chaotic:
        return create_shape(static_cast<ShapeType>(gen(rng)), result);
    }
  }

  auto ShapeFactory::create_shape(ShapeType type, bool& result) -> Shape
  {
    if(not m_map)
      throw std::runtime_error("ShapeFactory: map is invalid");
    switch(type) {
      case ShapeType::I: return create_i(result);
      case ShapeType::L: return create_l(result);
      case ShapeType::J: return create_j(result);
      case ShapeType::S: return create_s(result);
      case ShapeType::Z: return create_z(result);
      case ShapeType::T: return create_t(result);
      case ShapeType::B: return create_b(result);
      default: throw std::invalid_argument("Invalid shape type given");
    }
  }

  auto ShapeFactory::create_i(bool& result) -> Shape
  {
    auto hc = m_map->width() / 2;
    auto top = m_map->height() - 1;
    Shape shape {m_map};
    auto color = utils::Color::purple();
    auto new_block = m_map->create_block({{color}, {hc, top}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc - 1, top}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc + 1, top}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc + 2, top}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    result = true;
    return shape;
  }

  auto ShapeFactory::create_l(bool& result) -> Shape
  {
    auto hc = m_map->width() / 2;
    auto top = m_map->height() - 1;
    Shape shape {m_map};
    auto color = utils::Color::red();
    auto new_block = m_map->create_block({{color}, {hc, top - 1}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc + 1, top - 1}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc + 1, top}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc - 1, top - 1}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    result = true;
    return shape;
  }

  auto ShapeFactory::create_j(bool& result) -> Shape
  {
    auto hc = m_map->width() / 2;
    auto top = m_map->height() - 1;
    Shape shape {m_map};
    auto color = utils::Color::green();
    auto new_block = m_map->create_block({{color}, {hc, top - 1}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc + 1, top - 1}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc - 1, top}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc - 1, top - 1}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    result = true;
    return shape;
  }

  auto ShapeFactory::create_s(bool& result) -> Shape
  {
    auto hc = m_map->width() / 2;
    auto top = m_map->height() - 1;
    Shape shape {m_map};
    auto color = utils::Color::white();
    auto new_block = m_map->create_block({{color}, {hc, top}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc, top - 1}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc - 1, top - 1}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc + 1, top}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    result = true;
    return shape;
  }

  auto ShapeFactory::create_z(bool& result) -> Shape
  {
    auto hc = m_map->width() / 2;
    auto top = m_map->height() - 1;
    Shape shape {m_map};
    auto color = utils::Color::yellow();
    auto new_block = m_map->create_block({{color}, {hc, top}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc, top - 1}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc + 1, top - 1}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc - 1, top}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    result = true;
    return shape;
  }

  auto ShapeFactory::create_t(bool& result) -> Shape
  {
    auto hc = m_map->width() / 2;
    auto top = m_map->height() - 1;
    Shape shape {m_map};
    auto color = utils::Color::blue();
    auto new_block = m_map->create_block({{color}, {hc, top}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc, top - 1}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc + 1, top}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc - 1, top}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    result = true;
    return shape;
  }

  auto ShapeFactory::create_b(bool& result) -> Shape
  {
    auto hc = m_map->width() / 2;
    auto top = m_map->height() - 1;
    Shape shape {m_map};
    auto color = utils::Color::orange();
    auto new_block = m_map->create_block({{color}, {hc, top}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc, top - 1}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc + 1, top}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    new_block = m_map->create_block({{color}, {hc + 1, top - 1}});
    if(not new_block) {
      result = false;
      return shape;
    }
    shape.blocks().push_back(new_block);
    result = true;
    return shape;
  }

}  // namespace bluks::game
