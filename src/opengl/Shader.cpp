// Shader.cpp

#include "KaliLaska/opengl.hpp"
#include <GL/gl3w.h>

namespace KaliLaska {
namespace GL {
Shader::Shader(uint32_t openglShader)
    : openglShader_{openglShader} {
}

Shader::~Shader() {
  glDeleteShader(openglShader_);
}

Shader &Shader::operator=(Shader &&rhs) {
  glDeleteShader(openglShader_);
  openglShader_ = rhs.openglShader_;
  return *this;
}

uint32_t Shader::value() const {
  return openglShader_;
}
} // namespace GL
} // namespace KaliLaska
