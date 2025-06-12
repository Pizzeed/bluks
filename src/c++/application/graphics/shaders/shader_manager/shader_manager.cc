#include <battery/embed.hpp>
#include <stdexcept>
#include "application/graphics/shaders/shader_program/shader_program.h"
#include <application/graphics/shaders/shader_manager/shader_manager.h>

namespace bluks::graphics::shaders
{
  ShaderManager::ShaderManager()
  {
    m_programs.emplace(
      "simple_color",
      make_shader_program(
        b::embed<"src/shaders/default/default.vert.glsl">().str(),
        b::embed<"src/shaders/default/default.frag.glsl">().str()
      )
    );
    m_programs.emplace(
      "default_text",
      make_shader_program(
        b::embed<"src/shaders/simple_texture/simple_texture.vert.glsl">().str(),
        b::embed<"src/shaders/simple_texture/simple_texture.frag.glsl">().str()
      )
    );
    for(auto& p : m_programs)
      p.second.prepare();
  }

  auto ShaderManager::contains(std::string const& name) const -> bool
  {
    return m_programs.contains(name);
  }

  auto ShaderManager::program(std::string const& name) -> ShaderProgram const&
  {
    auto& prog = m_programs.at(name);
    if(not prog.is_ready())
      if(not prog.prepare())
        throw std::runtime_error(
          "Shader program named " + name
          + " is not ready and failed to prepare!"
        );
    return prog;
  }

  auto ShaderManager::insert(std::string const& name, ShaderProgram&& program)
    -> void
  {
    m_programs.emplace(name, std::move(program));
  }

  auto ShaderManager::emplace(
    std::string const& name,
    std::string const& vertex_shader,
    std::string const& fragment_shader
  ) -> void
  {
    m_programs
      .emplace(name, make_shader_program(vertex_shader, fragment_shader));
  }
}  // namespace bluks::graphics::shaders
