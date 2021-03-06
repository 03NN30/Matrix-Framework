#include "Texture.h"

namespace MX
{
  Texture::Texture(const std::string& path)
  {
    m_Name = path.substr(path.find_last_of("/") + 1);
    m_path = path;

    m_relative_path = path.substr(path.find(std::string("matrix")) + 7); // 7 = m + a + t + r + i + x + /
  }
}