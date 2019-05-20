// Texture.cpp

#include "KaliLaska/Picture.hpp"
#include "KaliLaska/opengl.hpp"
#include <GLES3/gl3.h>
#include <iostream>

namespace KaliLaska::GL {
// FIXME here we have problem, because we can initialize texture only after
// create opengl program
Texture::Texture(const Picture &fromRGBA32)
    : glTexture_{} {
  ::glActiveTexture(GL_TEXTURE7);
  ::glGenTextures(1, &glTexture_);
  ::glBindTexture(GL_TEXTURE_2D, glTexture_);

  auto pictureSize = fromRGBA32.size();
  ::glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 pictureSize.width(),
                 pictureSize.height(),
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 fromRGBA32.pixels());

  ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  ::glBindTexture(GL_TEXTURE_2D, 0);
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
} // namespace KaliLaska::GL
