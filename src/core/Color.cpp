// Color.cpp

#include "KaliLaska/Color.hpp"

namespace KaliLaska {
Color::Color(float r, float g, float b, float a)
    : r_{r}
    , g_{g}
    , b_{b}
    , a_{a} {
}

Color::Color(Colors color)
    : r_{}
    , g_{}
    , b_{}
    , a_{1} {
  switch (color) {
  case Colors::Black:
    break;
  case Colors::White:
    r_ = 1;
    g_ = 1;
    b_ = 1;
    break;
  case Colors::Gray:
    r_ = 0.5;
    g_ = 0.5;
    b_ = 0.5;
    break;
  case Colors::Red:
    r_ = 1;
    break;
  case Colors::Green:
    g_ = 1;
    break;
  case Colors::Blue:
    b_ = 1;
    break;
  case Colors::Magenta:
    r_ = 1;
    b_ = 1;
    break;
  case Colors::Yellow:
    r_ = 1;
    g_ = 1;
    break;
  case Colors::Cyan:
    g_ = 1;
    b_ = 1;
    break;
  default:
    break;
  }
}

void Color::setR(float r) {
  r_ = r;
}

void Color::setG(float g) {
  g_ = g;
}

void Color::setB(float b) {
  b_ = b;
}

void Color::setA(float a) {
  a_ = a;
}

float Color::r() const {
  return r_;
}

float Color::g() const {
  return g_;
}

float Color::b() const {
  return b_;
}

float Color::a() const {
  return a_;
}
} // namespace KaliLaska
