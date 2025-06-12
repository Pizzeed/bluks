#pragma once
#include <string>
#include <utils/types.h>

namespace bluks::graphics::shaders
{
  class ShaderProgram
  {
   public:
    ShaderProgram(
      std::string_view const& vertex,
      std::string_view const& fragment
    );

    ~ShaderProgram();

    auto vertex() const -> std::string const&;
    auto fragment() const -> std::string const&;
    auto compile() -> bool;
    auto link() -> bool;
    auto prepare() -> bool;
    auto error() const -> std::string const&;
    auto is_compiled() const -> bool;
    auto is_linked() const -> bool;
    auto is_ready() const -> bool;
    auto gl_program_id() const -> u32;
    auto gl_vshader_id() const -> u32;
    auto gl_fshader_id() const -> u32;

   private:
    std::string m_vertex = "";
    std::string m_fragment = "";
    std::string m_error = "";
    bool m_compiled = false;
    bool m_linked = false;
    u32 m_prog_id = -1;
    u32 m_v_id = -1;
    u32 m_f_id = -1;
  };
}  // namespace bluks::graphics::shaders
