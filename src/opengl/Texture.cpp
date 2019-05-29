// Texture.cpp

#include "KaliLaska/Picture.hpp"
#include "KaliLaska/opengl.hpp"
#include <GLES3/gl3.h>
#include <iostream>
#include <vector>

namespace KaliLaska::GL {

namespace bg = boost::geometry;

// FIXME here we have problem, because we can initialize texture only after
// create opengl program
Texture::Texture(const Picture &fromRGBA32)
    : Texture{
          fromRGBA32,
          Box{PointF{0, 0},
              PointF(fromRGBA32.size().width(), fromRGBA32.size().height())}} {
}

Texture::Texture(const Picture &fromRGBA32,
                 const Box &    box,
                 const Ring &   textureShape)
    : glTexture_{}
    , textureShape_{textureShape} {
  glActiveTexture(GL_TEXTURE7);
  glGenTextures(1, &glTexture_);
  glBindTexture(GL_TEXTURE_2D, glTexture_);

  auto pictureSize = fromRGBA32.size();
  int  defaultAlignment{};
  int  defaultRowLength{};
  glGetIntegerv(GL_UNPACK_ALIGNMENT, &defaultAlignment);
  glGetIntegerv(GL_UNPACK_ROW_LENGTH, &defaultRowLength);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, pictureSize.width());

  ::glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RGBA,
      bg::get<bg::max_corner, 0>(box) - bg::get<bg::min_corner, 0>(box),
      bg::get<bg::max_corner, 1>(box) - bg::get<bg::min_corner, 1>(box),
      0,
      GL_RGBA,
      GL_UNSIGNED_BYTE,
      fromRGBA32.pixels() +
          static_cast<int>(
              (pictureSize.width() * bg::get<bg::min_corner, 1>(box) +
               bg::get<bg::min_corner, 0>(box))) *
              4);

  glPixelStorei(GL_UNPACK_ALIGNMENT, defaultAlignment);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, defaultRowLength);

  ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
  if (glTexture_) {
    ::glDeleteTextures(1, &glTexture_);
  }
}

Texture::Texture(Texture &&rhs)
    : glTexture_{rhs.glTexture_} {
  rhs.glTexture_ = 0;
}

Texture &Texture::operator=(Texture &&rhs) {
  if (glTexture_) {
    glDeleteTextures(1, &glTexture_);
  }

  glTexture_     = rhs.glTexture_;
  rhs.glTexture_ = 0;

  return *this;
}

void Texture::bind(bool val) const {
  if (val) {
    glBindTexture(GL_TEXTURE_2D, glTexture_);
  } else {
    glBindTexture(GL_TEXTURE_2D, 0);
  }
}

const Ring &Texture::shape() const {
  return textureShape_;
}
} // namespace KaliLaska::GL
