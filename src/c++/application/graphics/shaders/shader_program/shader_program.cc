#include <application/graphics/glad/glad.h>
#include <application/graphics/shaders/shader_program/shader_program.h>

namespace bluks::graphics::shaders
{
  ShaderProgram::ShaderProgram(
    std::string_view const& vertex,
    std::string_view const& fragment
  )
    : m_vertex(vertex)
    , m_fragment(fragment)
  {
    m_prog_id = glCreateProgram();
    m_v_id = glCreateShader(GL_VERTEX_SHADER);
    m_f_id = glCreateShader(GL_FRAGMENT_SHADER);
    auto v_str = m_vertex.c_str();
    auto f_str = m_fragment.c_str();
    glShaderSource(m_v_id, 1, &v_str, nullptr);
    glShaderSource(m_f_id, 1, &f_str, nullptr);
  }

  ShaderProgram::~ShaderProgram()
  {
    glDeleteShader(m_v_id);
    glDeleteShader(m_f_id);
    glDeleteProgram(m_prog_id);
  }

  auto ShaderProgram::vertex() const -> std::string const& { return m_vertex; }

  auto ShaderProgram::fragment() const -> std::string const&
  {
    return m_fragment;
  }

  auto ShaderProgram::compile() -> bool
  {
    if(m_compiled)
      return true;
    glCompileShader(m_v_id);
    glCompileShader(m_f_id);

    int vsuc, fsuc;
    char vinfoLog[512], finfoLog[512];
    glGetShaderiv(m_v_id, GL_COMPILE_STATUS, &vsuc);
    glGetShaderiv(m_f_id, GL_COMPILE_STATUS, &fsuc);

    if(not vsuc) {
      glGetShaderInfoLog(m_v_id, 512, nullptr, vinfoLog);
      m_error = vinfoLog;
      return false;
    }
    if(not fsuc) {
      glGetShaderInfoLog(m_f_id, 512, nullptr, finfoLog);
      m_error = finfoLog;
      return false;
    }
    m_compiled = true;
    return true;
  }

  auto ShaderProgram::link() -> bool
  {
    if(m_linked)
      return true;
    if(not m_compiled) {
      m_error = "Shader program was not compiled yet, but link() was called";
      return false;
    }
    glAttachShader(m_prog_id, m_v_id);
    glAttachShader(m_prog_id, m_f_id);
    glLinkProgram(m_prog_id);

    int suc;
    char infoLog[512];
    glGetProgramiv(m_prog_id, GL_LINK_STATUS, &suc);

    if(not suc) {
      glGetProgramInfoLog(m_prog_id, 512, nullptr, infoLog);
      m_error = infoLog;
      return false;
    }
    m_linked = true;
    return true;
  }

  auto ShaderProgram::prepare() -> bool
  {
    auto res = this->compile();
    res &= this->link();
    return res;
  }

  auto ShaderProgram::is_compiled() const -> bool { return m_compiled; }

  auto ShaderProgram::is_linked() const -> bool { return m_linked; }

  auto ShaderProgram::is_ready() const -> bool
  {
    return m_compiled && m_linked && m_error == "";
  }

}  // namespace bluks::graphics::shaders
