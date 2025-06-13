#include <algorithm>
#include <iostream>

#include <game_base/shapes/shape_factory.h>
#include <game_base/bluks_game/bluks_game.h>

namespace bluks::game
{
  BluksGame::BluksGame() {}

  auto BluksGame::tick() -> void
  {
    if(m_state == GameState::Ongoing && not m_current_shape.move_down()) {
      check_lines();
      spawn_new_shape();
    }
  }

  auto BluksGame::check_lines() -> void
  {
    auto& blocks = m_map.blocks();
    std::vector<int> row_counts(m_map.height(), 0);
    for(auto const& block : blocks) {
      if(block->position().y >= 0 && block->position().y < m_map.height()) {
        row_counts[block->position().y]++;
      }
    }

    std::vector<int> full_rows;
    for(int y = 0; y < m_map.height(); ++y) {
      if(row_counts[y] == m_map.width()) {
        full_rows.push_back(y);
      }
    }

    if(not full_rows.empty()) {
      blocks.erase(
        std::remove_if(
          blocks.begin(),
          blocks.end(),
          [&](std::shared_ptr<Block> const& b) {
            return std::
                     find(full_rows.begin(), full_rows.end(), b->position().y)
                != full_rows.end();
          }
        ),
        blocks.end()
      );

      std::sort(full_rows.begin(), full_rows.end());
      for(auto& block : blocks) {
        if(block->position().y > full_rows.back()) {
          block->position().y -= full_rows.size();
        }
      }
    }
    switch(full_rows.size()) {
      case 4: m_score += 100; break;
      case 3: m_score += 30; break;
      case 2: m_score += 20; break;
      case 1: m_score += 10; break;
      default: m_score += full_rows.size() * 10; break;
    }
  }

  auto BluksGame::spawn_new_shape() -> void
  {
    static ShapeFactory factory {&m_map};
    bool res = false;
    m_current_shape = factory.create_random_shape(res);
    if(not res) {
      game_over();
    }
  }

  auto BluksGame::start() -> void
  {
    m_score = 0;
    m_state = GameState::Ongoing;
    m_map.blocks().clear();
    spawn_new_shape();
  }

  auto BluksGame::game_over() -> void
  {
    m_state = GameState::GameOver;
    std::cout << "Game Over!" << std::endl;
  }

  auto BluksGame::pause() -> void
  {  // TODO
  }

  auto BluksGame::unpause() -> void
  {  // TODO
  }
}  // namespace bluks::game
