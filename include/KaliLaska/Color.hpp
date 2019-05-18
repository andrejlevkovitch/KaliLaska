// Color.hpp

#pragma once

#include <cstdint>

namespace KaliLaska {
/**\brief represent RGBA color
 */
class Color final {
public:
  enum class Colors {
    Black,
    White,
    Gray,
    Red,
    Green,
    Blue,
    Magenta,
    Yellow,
    Cyan
  };
  /**\brief input values from 0 to 1
   */
  Color(float r, float g, float b, float a = 1);

  /**\brief get color from enum
   * \warning alfa chanel will be always equal to 1
   */
  Color(Colors color);

  void setR(float r);
  void setG(float g);
  void setB(float b);
  void setA(float a);

  float r() const;
  float g() const;
  float b() const;
  float a() const;

  bool operator==(const Color &rhs);
  bool operator!=(const Color &rhs);

private:
  float r_;
  float g_;
  float b_;
  float a_;
};
} // namespace KaliLaska
