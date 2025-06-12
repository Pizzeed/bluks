#pragma once
#include <string>

#include <utils/color.h>
#include <utils/types.h>
#include <application/graphics/shaders/shader_program/shader_program.h>
#include <application/graphics/text/font.h>

namespace bluks::app
{
  class TextRender
  {
   public:
    TextRender(
      std::u32string_view const& text = U"Sample Text",
      f32 x = .0,
      f32 y = .0,
      Font const& font = Font::get_default(),
      utils::Color const& color = utils::Color::white()
    );
    TextRender(
      std::u32string_view&& text,
      f32 x = .0,
      f32 y = .0,
      Font const& font = Font::get_default(),
      utils::Color const& color = utils::Color::white()
    );

    auto render(graphics::shaders::ShaderProgram const& material) -> void;

   private:
    auto prepare_buffers() -> void;

    std::u32string m_text;
    Font m_font;
    utils::Color m_color;
    f32 m_x, m_y;
    u32 m_vao, m_vbo, m_ebo;
  };
}  // namespace bluks::app
