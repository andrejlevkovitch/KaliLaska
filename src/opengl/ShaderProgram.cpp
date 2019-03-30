// ShaderProgram.cpp

#include "KaliLaska/opengl.hpp"
#include <GL/gl3w.h>
#include <stdexcept>

namespace KaliLaska::GL {
// just throw exception
void getLog(uint32_t prog) {
  GLint lenght;
  glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &lenght);
  std::string log;
  log.resize(lenght);
  glGetProgramInfoLog(prog, lenght, nullptr, &log[0]);
  throw std::runtime_error{log};
}

enum class ShaderOpenGLType_ { Vertex, Fragment };
uint32_t createShader(ShaderOpenGLType_ type, std::string_view code) {
  uint32_t openglShader{};
  switch (type) {
  case ShaderOpenGLType_::Vertex:
    openglShader = glCreateShader(GL_VERTEX_SHADER);
    break;
  case ShaderOpenGLType_::Fragment:
    openglShader = glCreateShader(GL_FRAGMENT_SHADER);
    break;
  default:
    throw std::runtime_error{"unexpected shader type"};
  }

  if (!openglShader) {
    throw std::runtime_error{"opengl shader can not be created"};
  }

  auto codePtr = code.data();
  glShaderSource(openglShader, 1, &codePtr, nullptr);

  glCompileShader(openglShader);

  // check status after compile
  GLint status{};
  glGetShaderiv(openglShader, GL_COMPILE_STATUS, &status);

  // if somthing wrong
  if (!status) {
    GLint lenght{};
    glGetShaderiv(openglShader, GL_INFO_LOG_LENGTH, &lenght);
    std::string log{};
    log.resize(lenght);
    glGetShaderInfoLog(openglShader, lenght, nullptr, &log[0]);

    glDeleteShader(openglShader);
    throw std::runtime_error{log};
  }
  return openglShader;
}

uint32_t createProgram() {
  uint32_t retval = glCreateProgram();
  if (!retval) {
    throw std::runtime_error{"opengl program can not be created"};
  }
  return retval;
}

ShaderProgram::ShaderProgram(std::string_view vertexShaderCode,
                             std::string_view fragmentShaderCode)
    : program_{}
    , vertexShader_{}
    , fragmentShader_{} {
  try {
    vertexShader_ = createShader(ShaderOpenGLType_::Vertex, vertexShaderCode);
    fragmentShader_ =
        createShader(ShaderOpenGLType_::Fragment, fragmentShaderCode);

    program_ = createProgram();
  } catch (const std::runtime_error &) {
    throw;
  }

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
}

ShaderProgram::~ShaderProgram() {
  glDetachShader(program_, fragmentShader_);
  glDetachShader(program_, vertexShader_);

  glDeleteShader(fragmentShader_);
  glDeleteShader(vertexShader_);
  glDeleteProgram(program_);
}

void ShaderProgram::use() {
  glUseProgram(program_);
  if (glGetError() != GL_NO_ERROR) {
    throw std::runtime_error{"program can not be used"};
  }
}

ShaderProgram::ShaderProgram(ShaderProgram &&rhs)
    : program_{rhs.program_}
    , vertexShader_{rhs.vertexShader_}
    , fragmentShader_{rhs.fragmentShader_} {
  rhs.vertexShader_   = 0;
  rhs.fragmentShader_ = 0;
  rhs.program_        = 0;
}

ShaderProgram &ShaderProgram::operator=(ShaderProgram &&rhs) {
  glDetachShader(program_, fragmentShader_);
  glDetachShader(program_, vertexShader_);

  glDeleteShader(fragmentShader_);
  glDeleteShader(vertexShader_);
  glDeleteProgram(program_);

  program_        = rhs.program_;
  vertexShader_   = rhs.vertexShader_;
  fragmentShader_ = rhs.fragmentShader_;

  rhs.vertexShader_   = 0;
  rhs.fragmentShader_ = 0;
  rhs.program_        = 0;

  return *this;
}
} // namespace KaliLaska::GL
