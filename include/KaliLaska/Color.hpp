// Color.hpp

#pragma once

#include <cstdint>

namespace KaliLaska {
/**\brief represent RGBA color. You can use pointer to the struct like pointer
 * to 4 (or less) floats
 */
struct Color final {
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

  bool operator==(const Color &rhs);
  bool operator!=(const Color &rhs);

public:
  float r;
  float g;
  float b;
  float a;
};
} // namespace KaliLaska
