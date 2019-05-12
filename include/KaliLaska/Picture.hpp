// Picture.hpp

#pragma once

#include "KaliLaska/Size.hpp"
#include "kalilaska_export.h"
#include <filesystem>
#include <string_view>
#include <vector>

namespace KaliLaska {
class KALILASKA_EXPORT Picture final {
public:
  /**\brief load picture from file (png)
   */
  Picture(const std::filesystem::path &file);
  ~Picture();

  /**\return true if Picture is valid, and false - otherwise
   */
  bool isValid() const;

  /**\return current size of Picture, {0, 0} - if Picture is invalid
   */
  Size size() const;

  /**\brief using for load by OpenGL
   */
  const unsigned char *pixels() const;

private:
  Size                       size_;
  std::vector<unsigned char> decodedPNG_;
};
} // namespace KaliLaska
