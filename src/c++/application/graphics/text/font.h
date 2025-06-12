#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include <stb_truetype.h>

#include <utils/types.h>
#include <application/graphics/glad/glad.h>

namespace bluks::app
{
  class Font
  {
   public:
    inline static auto get_default() -> Font const& { return m_default; }

    inline static auto set_default(Font const& font) -> void
    {
      m_default = font;
    }

    inline static auto set_default(Font&& font) -> void
    {
      m_default = std::move(font);
    }

    Font(std::vector<u8> const& ttf_raw, f32 scale = 32);

    inline auto stb_info() const -> stbtt_fontinfo const& { return m_stb_info; }

    inline auto scale() const -> float { return m_scale; }

    auto cache_glyph(u32 glyph) -> void;
    auto cache_glyphs(std::u32string_view const& str) -> void;
    auto tex_of_glyph(u32 glyph_code) const -> u32;

   private:
    static Font m_default;
    f32 m_scale = 32;
    stbtt_fontinfo m_stb_info;
    std::unordered_map<u32, u32> m_glyph_cache;
  };
}  // namespace bluks::app
