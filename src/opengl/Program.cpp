// Program.cpp

#include "KaliLaska/opengl.hpp"
#include <GL/gl3w.h>

namespace KaliLaska {
namespace GL {
Program::Program(uint32_t openglProgram)
    : openglProgram_{openglProgram} {
}

Program::~Program() {
  glDeleteProgram(openglProgram_);
}

Program &Program::operator=(Program &&rhs) {
  glDeleteProgram(openglProgram_);
  openglProgram_ = rhs.openglProgram_;
  return *this;
}

uint32_t Program::value() const {
  return openglProgram_;
}
} // namespace GL
} // namespace KaliLaska
