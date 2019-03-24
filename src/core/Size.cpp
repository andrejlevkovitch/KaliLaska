// Size.hpp

#include "KaliLaska/Size.hpp"

namespace KaliLaska {

Size::Size()
    : width_{}
    , height_{} {
}

Size::Size(int width, int height)
    : width_{width}
    , height_{height} {
}

int Size::width() const {
  return width_;
}

int Size::height() const {
  return height_;
}

void Size::setWidth(int width) {
  width_ = width;
}

void Size::setHeight(int height) {
  height_ = height;
}

bool Size::operator!=(const Size &rhs) const {
  return (width_ != rhs.width_ || height_ != rhs.height_);
}

bool Size::operator==(const Size &rhs) const {
  return (width_ == rhs.width_ && height_ == rhs.height_);
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &stream, const KaliLaska::Size &size) {
  stream << "width " << size.width() << ", height " << size.height();
  return stream;
}
