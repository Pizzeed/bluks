#pragma once

#include <string>

#include <utils/types.h>

namespace bluks::game
{
  class Color
  {
   public:
    Color() {}

    Color(u8 r, u8 g, u8 b, u8 a)
      : m_r(r)
      , m_g(g)
      , m_b(b)
      , m_a(a)
    {}

    Color(u8 r, u8 g, u8 b)
      : m_r(r)
      , m_g(g)
      , m_b(b)
      , m_a(0xff)
    {}

    Color(std::string const& hex);

    inline auto r() const -> u8 { return m_r; }

    inline auto g() const -> u8 { return m_g; }

    inline auto b() const -> u8 { return m_b; }

    inline auto hex_rgb() const -> std::string;

    inline auto hex_rgba() const -> std::string;

    inline static auto red() -> Color { return {255, 0, 0}; }

    inline static auto green() -> Color { return {0, 255, 0}; }

    inline static auto blue() -> Color { return {255, 255, 0}; }

    inline static auto yellow() -> Color { return {255, 255, 0}; }

    inline static auto purple() -> Color { return {255, 0, 255}; }

    inline static auto cyan() -> Color { return {0, 255, 255}; }

    inline static auto orange() -> Color { return {255, 122, 0}; }

    inline static auto black() -> Color { return {}; }

    inline static auto white() -> Color { return {255, 255, 255}; }

   private:
    u8 m_r = 0;
    u8 m_g = 0;
    u8 m_b = 0;
    u8 m_a = 255;
  };
}  // namespace bluks::game
