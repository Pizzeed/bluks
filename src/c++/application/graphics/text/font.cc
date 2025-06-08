#include <application/graphics/text/font.h>

namespace bluks::app
{
  Font::Font(std::vector<u8> const& ttf_raw, float scale)
    : m_scale(scale)
  {
    stbtt_InitFont(
      &m_stb_info,
      ttf_raw.data(),
      stbtt_GetFontOffsetForIndex(ttf_raw.data(), 0)
    );
  }

  auto Font::cache_glyph(u32 glyph_code) -> void
  {
    if(m_glyph_cache.contains(glyph_code))
      return;
    auto pix_scale = stbtt_ScaleForPixelHeight(&m_stb_info, m_scale);
    int w, h, x, y;
    u8* glyphBitmap = stbtt_GetCodepointBitmap(
      &m_stb_info,
      0,
      pix_scale,
      glyph_code,
      &w,
      &h,
      &x,
      &y
    );
    u32 tex_id;
    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RED,
      w,
      h,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      glyphBitmap
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_glyph_cache.emplace(glyph_code, tex_id);
  }

  auto Font::cache_glyphs(std::u32string const& str) -> void
  {
    for(auto g : str)
      cache_glyph(g);
  }

  auto Font::tex_of_glyph(u32 glyph_code) const -> u32
  {
    return m_glyph_cache.at(glyph_code);
  }

}  // namespace bluks::app
