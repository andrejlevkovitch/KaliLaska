// Attacher.cpp

#include "KaliLaska/opengl.hpp"
#include <GL/gl3w.h>
#include <stdexcept>

namespace KaliLaska {
namespace GL {

// just throw exception
void getLog(uint32_t prog) {
  GLint lenght;
  glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &lenght);
  std::string log;
  log.resize(lenght);
  glGetProgramInfoLog(prog, lenght, nullptr, &log[0]);
  throw std::runtime_error{log};
}

Attacher::Attacher(const Program &program,
                   const Shader & vertexShader,
                   const Shader & fragmentShader)
    : program_{program.value()}
    , vertexShader_{vertexShader.value()}
    , fragmentShader_{fragmentShader.value()} {
  for (auto i : {vertexShader_, fragmentShader_}) {
    glAttachShader(program_, i);
    switch (glGetError()) {
    case GL_NO_ERROR:
      break;
    case GL_INVALID_VALUE:
      throw std::runtime_error{"invalid value"};
    case GL_INVALID_OPERATION:
      throw std::runtime_error{"shader can not be attached"};
    default:
      throw std::runtime_error{"unexpected error"};
    }
  }

  glLinkProgram(program_);

  // get status of linkage
  GLint status{};
  glGetProgramiv(program_, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    getLog(program_);
  }

  glUseProgram(program_);
  if (glGetError() != GL_NO_ERROR) {
    throw std::runtime_error{"program can not be used"};
  }
}

Attacher::~Attacher() {
  glDetachShader(program_, vertexShader_);
  glDetachShader(program_, fragmentShader_);
}

Attacher &Attacher::operator=(Attacher &&rhs) {
  glDetachShader(program_, vertexShader_);
  glDetachShader(program_, fragmentShader_);

  program_        = rhs.program_;
  vertexShader_   = rhs.vertexShader_;
  fragmentShader_ = rhs.fragmentShader_;

  return *this;
}
} // namespace GL
} // namespace KaliLaska
