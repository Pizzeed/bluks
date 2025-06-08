#pragma once
#include <unordered_map>
#include <vector>

#include <stb_truetype.h>

#include <utils/color.h>
#include <utils/types.h>
#include <application/graphics/glad/glad.h>

namespace bluks::app
{
  class Font
  {
   public:
    inline static auto Default() -> Font const& { return m_default; }

    inline static auto set_default(Font const& font) -> void
    {
      m_default = font;
    }

    inline static auto set_default(Font&& font) -> void
    {
      m_default = std::move(font);
    }

    Font(std::vector<u8> const& ttf_raw, float scale = 32);

    auto cache_glyph(u32 glyph) -> void;
    auto cache_glyphs(std::u32string const& str) -> void;
    auto tex_of_glyph(u32 glyph_code) const -> u32;

   private:
    static Font m_default;
    float m_scale = 32;
    stbtt_fontinfo m_stb_info;
    std::unordered_map<u32, u32> m_glyph_cache;
  };
}  // namespace bluks::app
