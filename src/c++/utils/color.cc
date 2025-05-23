#include <utils/color.h>

#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>

namespace bluks::game
{
  auto Color::hex_rgb() const -> std::string
  {
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(m_r)
       << static_cast<int>(m_g) << static_cast<int>(m_b) << static_cast<int>(m_r);
    return ss.str();
  }

  auto Color::hex_rgba() const -> std::string
  {
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(m_r)
       << static_cast<int>(m_g) << static_cast<int>(m_b) << static_cast<int>(m_r)
       << static_cast<int>(m_a);
    return ss.str();
  }

  Color::Color(std::string const& hex)
  {
    if(hex.empty() || hex[0] != '#' || (hex.length() != 7 && hex.length() != 9)) {
      throw std::invalid_argument("Invalid color format");
    }

    auto hexToInt = [](std::string const& s) -> int { return std::stoi(s, nullptr, 16); };

    m_r = hexToInt(hex.substr(1, 2));
    m_g = hexToInt(hex.substr(3, 2));
    m_b = hexToInt(hex.substr(5, 2));
    if(hex.length() == 9) {
      m_a = hexToInt(hex.substr(7, 2));
    }
    else {
      m_a = 255;
    }
  }

}  // namespace bluks::game
