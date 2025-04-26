#include <string>
#include <sstream>
#include <iomanip>
#include <utils/color.h>

namespace bluks_game
{
  auto Color::hex_rgb() const -> std::string
  {
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(m_r)
       << static_cast<int>(m_g) << static_cast<int>(m_b)
       << static_cast<int>(m_r);
    return ss.str();
  }

  auto Color::hex_rgba() const -> std::string
  {
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(m_r)
       << static_cast<int>(m_g) << static_cast<int>(m_b)
       << static_cast<int>(m_r) << static_cast<int>(m_a);
    return ss.str();
  }
}  // namespace bluks_game
