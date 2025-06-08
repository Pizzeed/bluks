#pragma once
#include <string>

#include <utils/types.h>
#include <application/graphics/text/font.h>

namespace bluks::app
{
  class TextRender
  {
   public:
    TextRender(
      std::string const& text = "Sample Text",
      Font const& font = Font::Default
    );

    auto setup_render_buffer(u32 buffer);
  };
}  // namespace bluks::app
