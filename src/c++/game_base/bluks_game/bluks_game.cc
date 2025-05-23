#include <game_base/bluks_game/bluks_game.h>
#include <iostream>

namespace bluks::game
{
  BluksGame::BluksGame() {}

  auto BluksGame::tick() -> void {}

  auto BluksGame::spawn_new_shape() -> Shape const& {}

  auto BluksGame::start() -> void {}

  auto BluksGame::pause() -> void {}

  auto BluksGame::unpause() -> void {}
}  // namespace bluks::game
