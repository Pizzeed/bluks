#include <iostream>

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

  ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
    : m_vertex(std::move(other.m_vertex))
    , m_fragment(std::move(other.m_fragment))
    , m_error(std::move(other.m_error))
    , m_compiled(other.m_compiled)
    , m_linked(other.m_linked)
    , m_prog_id(other.m_prog_id)
    , m_v_id(other.m_v_id)
    , m_f_id(other.m_f_id)
  {
    if(this == &other)
      return;
    other.m_prog_id = 0;
    other.m_v_id = 0;
    other.m_f_id = 0;
    other.m_compiled = false;
    other.m_linked = false;
  }

  auto ShaderProgram::operator=(ShaderProgram&& other) noexcept
    -> ShaderProgram&
  {
    if(this == &other)
      return *this;
    m_vertex = std::move(other.m_vertex);
    m_fragment = std::move(other.m_fragment);
    m_error = std::move(other.m_error);
    m_compiled = other.m_compiled;
    m_linked = other.m_linked;

    m_prog_id = other.m_prog_id;
    m_v_id = other.m_v_id;
    m_f_id = other.m_f_id;

    other.m_prog_id = 0;
    other.m_v_id = 0;
    other.m_f_id = 0;
    other.m_compiled = false;
    other.m_linked = false;

    return *this;
  }

  auto make_shader_program(
    std::string_view const& vsrc,
    std::string_view const& fsrc
  ) -> ShaderProgram
  {
    return {vsrc, fsrc};
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

  auto ShaderProgram::gl_program_id() const -> u32 { return m_prog_id; }

  auto ShaderProgram::gl_vshader_id() const -> u32 { return m_v_id; }

  auto ShaderProgram::gl_fshader_id() const -> u32 { return m_f_id; }

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
      std::cout << "Error in vertex shader compilation: " << m_error
                << "\nSource code:\n"
                << m_vertex << std::endl;
      return false;
    }
    if(not fsuc) {
      glGetShaderInfoLog(m_f_id, 512, nullptr, finfoLog);
      m_error = finfoLog;
      std::cout << "Error in fragment shader compilation: " << m_error
                << "\nSource code:\n"
                << m_fragment << std::endl;
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
      std::cout << "Error in shader program linkage process: " << m_error
                << std::endl;
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

  auto ShaderProgram::error() const -> std::string const& { return m_error; }

  auto ShaderProgram::is_compiled() const -> bool { return m_compiled; }

  auto ShaderProgram::is_linked() const -> bool { return m_linked; }

  auto ShaderProgram::is_ready() const -> bool
  {
    return m_compiled && m_linked;
  }

}  // namespace bluks::graphics::shaders
