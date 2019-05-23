// Color.cpp

#include "KaliLaska/Color.hpp"
#include <tuple>

namespace KaliLaska {
Color::Color(float r_, float g_, float b_, float a_)
    : r{r_}
    , g{g_}
    , b{b_}
    , a{a_} {
}

Color::Color(Colors color)
    : r{}
    , g{}
    , b{}
    , a{1} {
  switch (color) {
  case Colors::Black:
    break;
  case Colors::White:
    r = 1;
    g = 1;
    b = 1;
    break;
  case Colors::Gray:
    r = 0.5;
    g = 0.5;
    b = 0.5;
    break;
  case Colors::Red:
    r = 1;
    break;
  case Colors::Green:
    g = 1;
    break;
  case Colors::Blue:
    b = 1;
    break;
  case Colors::Magenta:
    r = 1;
    b = 1;
    break;
  case Colors::Yellow:
    r = 1;
    g = 1;
    break;
  case Colors::Cyan:
    g = 1;
    b = 1;
    break;
  default:
    break;
  }
}

bool Color::operator==(const Color &rhs) {
  if (std::tie(r, g, b, a) == std::tie(rhs.r, rhs.g, rhs.b, rhs.a)) {
    return true;
  }
  return false;
}

bool Color::operator!=(const Color &rhs) {
  if (*this == rhs) {
    return false;
  }
  return true;
}
} // namespace KaliLaska
