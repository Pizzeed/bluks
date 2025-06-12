#pragma once
#include <string>
#include <unordered_map>
#include <application/graphics/shaders/shader_program/shader_program.h>

namespace bluks::graphics::shaders
{
  class ShaderManager
  {
   public:
    ShaderManager();
    auto contains(std::string const& name) const -> bool;
    auto program(std::string const& name) const -> ShaderProgram const&;
    auto insert(std::string const& name, ShaderProgram const& program) -> void;
    auto emplace(
      std::string const& name,
      std::string const& vertex_shader,
      std::string const& fragment_shader
    ) -> void;

   private:
    std::unordered_map<std::string, ShaderProgram> m_programs = {};
  };
};  // namespace bluks::graphics::shaders
