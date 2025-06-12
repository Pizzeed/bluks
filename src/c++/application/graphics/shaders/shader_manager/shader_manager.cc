#include <battery/embed.hpp>
#include <application/graphics/shaders/shader_manager/shader_manager.h>

namespace bluks::graphics::shaders
{
  ShaderManager::ShaderManager()
  {
    m_programs.emplace(
      "simple_color",
      ShaderProgram {
        b::embed<"src/shaders/default/default.vert.glsl">().str(),
        b::embed<"src/shaders/default/default.frag.glsl">().str(),
      }
    );
    m_programs.emplace(
      "default_text",
      ShaderProgram {
        b::embed<"src/shaders/simple_texture/simple_texture.vert.glsl">().str(),
        b::embed<"src/shaders/simple_texture/simple_texture.frag.glsl">().str(),
      }
    );
  }

  auto ShaderManager::contains(std::string const& name) const -> bool { ret }

  auto ShaderManager::program(std::string const& name) const
    -> ShaderProgram const&
  {}

  auto ShaderManager::insert(
    std::string const& name,
    ShaderProgram const& program
  ) -> void
  {}

  auto ShaderManager::emplace(
    std::string const& name,
    std::string const& vertex_shader,
    std::string const& fragment_shader
  ) -> void
  {}

}  // namespace bluks::graphics::shaders
