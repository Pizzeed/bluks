#include <iostream>
#include <string>
#include <utils/color.h>
#include <application/graphics/text/text_render.h>

namespace bluks::app
{
  TextRender::TextRender(
    std::u32string_view const& text,
    f32 x,
    f32 y,
    Font const& font,
    utils::Color const& color
  )
    : m_text(text)
    , m_font(font)
    , m_color(color)
  {
    m_font.cache_glyphs(m_text);
  }

  TextRender::TextRender(
    std::u32string_view&& text,
    f32 x,
    f32 y,
    Font const& font,
    utils::Color const& color
  )
    : m_text(std::move(text))
    , m_font(font)
    , m_color(color)
  {
    m_font.cache_glyphs(m_text);
  }

  auto TextRender::prepare_buffers() -> void
  {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    u32 indices[] = {
      0,
      1,
      2,
      0,
      2,
      3,
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(
      GL_ELEMENT_ARRAY_BUFFER,
      sizeof(indices),
      indices,
      GL_STATIC_DRAW
    );

    // Attribute 0: vec3 position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      8 * sizeof(f32),
      (void*)(0)
    );  // offset 0

    // Attribute 1: vec3 color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
      1,
      3,
      GL_FLOAT,
      GL_FALSE,
      8 * sizeof(f32),
      (void*)(3 * sizeof(f32))
    );  // offset after 3 f32s

    // Attribute 2: vec2 texcoord
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
      2,
      2,
      GL_FLOAT,
      GL_FALSE,
      8 * sizeof(f32),
      (void*)(6 * sizeof(f32))
    );  // offset after 6 f32s

    glBindVertexArray(0);
  }

  using namespace bluks::graphics::shaders;

  auto TextRender::render(ShaderProgram const& material) -> void
  {
    if(not material.is_ready())
      std::cout << "Unable to render text: material is not ready" << std::endl;

    glUseProgram(material.gl_program_id());

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_vao);

    auto const& info = m_font.stb_info();
    auto const& scale = m_font.scale();
    auto pix_scale = stbtt_ScaleForPixelHeight(&info, scale);
    auto off = 0;

    u32 vbo;

    for(int i = 0; i < m_text.size(); ++i) {
      auto const& c = m_text[i];
      auto tex_id = m_font.tex_of_glyph(c);

      int x0, y0, x1, y1;
      stbtt_GetCodepointBitmapBox(
        &info,
        c,
        pix_scale,
        pix_scale,
        &x0,
        &y0,
        &x1,
        &y1
      );

      f32 xpos = off + x0 * scale;
      f32 ypos = m_y + y0 * scale;
      f32 w = (x1 - x0) * scale;
      f32 h = (y1 - y0) * scale;
      off += w;

      // Vertex data: 4 vertices, 8 f32s each (x, y, z, r, g, b, u, v)
      f32 verts[4][8] =
        {{xpos,
          ypos + h,
          .0,
          m_color.rf(),
          m_color.gf(),
          m_color.bf(),
          0.0f,
          0.0f},
         {
           xpos,
           ypos,
           .0,
           m_color.rf(),
           m_color.gf(),
           m_color.bf(),
           0.0f,
           1.0f,
         },
         {
           xpos + w,
           ypos,
           .0,
           m_color.rf(),
           m_color.gf(),
           m_color.bf(),
           1.0f,
           1.0f,
         },
         {
           xpos + w,
           ypos + h,
           .0,
           m_color.rf(),
           m_color.gf(),
           m_color.bf(),
           1.0f,
           0.0f,
         }};
      glGenBuffers(1, &vbo);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
      glBindTexture(GL_TEXTURE_2D, tex_id);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glDeleteBuffers(1, &vbo);
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

}  // namespace bluks::app
