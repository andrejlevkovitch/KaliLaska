// Program.cpp

#include "KaliLaska/opengl.hpp"
#include "debug.hpp"
#include "logger/logger.hpp"
#include <GLES3/gl3.h>
#include <stdexcept>

namespace KaliLaska::GL {
// just throw exception
std::string getProgramLog(uint32_t prog) {
  std::string log{};
  GLint       lenght{};
  glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &lenght);
  log.resize(lenght);
  glGetProgramInfoLog(prog, lenght, nullptr, &log[0]);
  return log;
}

std::string getShaderLog(uint32_t shader) {
  std::string log{};
  GLint       lenght{};
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &lenght);
  log.resize(lenght);
  glGetShaderInfoLog(shader, lenght, nullptr, &log[0]);
  return log;
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
    LOG_THROW(std::invalid_argument, "unexpected shader type");
  }

  if (!openglShader) {
    LOG_THROW(std::logic_error, "opengl shader can not be created");
  }

  auto  codePtr = code.data();
  GLint size    = code.size();
  glShaderSource(openglShader, 1, &codePtr, &size);

  glCompileShader(openglShader);

  // check status after compile
  GLint status{};
  glGetShaderiv(openglShader, GL_COMPILE_STATUS, &status);

  // if somthing wrong
  if (!status) {
    auto log = getShaderLog(openglShader);
    glDeleteShader(openglShader);
    LOG_THROW(std::logic_error, log);
  }
  return openglShader;
}

uint32_t createProgram() {
  uint32_t retval = glCreateProgram();
  if (!retval) {
    LOG_THROW(std::logic_error, "opengl program can not be created");
  }
  return retval;
}

Program::Program(std::string_view vertexShaderCode,
                 std::string_view fragmentShaderCode)
    : program_{}
    , vertexShader_{}
    , fragmentShader_{} {
  LOG_TRACE << "GL::Program: konstructor";
  try {
    vertexShader_ = createShader(ShaderOpenGLType_::Vertex, vertexShaderCode);
    fragmentShader_ =
        createShader(ShaderOpenGLType_::Fragment, fragmentShaderCode);

    program_ = createProgram();
  } catch (const std::exception &) {
    throw;
  }

  for (auto i : {vertexShader_, fragmentShader_}) {
    glAttachShader(program_, i);
    switch (glGetError()) {
    case GL_NO_ERROR:
      break;
    case GL_INVALID_VALUE:
      LOG_THROW(std::invalid_argument, "invalid value");
    case GL_INVALID_OPERATION:
      LOG_THROW(std::logic_error, "shader can not be attached");
    default:
      LOG_THROW(std::runtime_error, "unexpected error");
    }
  }

  glLinkProgram(program_);

  // get status of linkage
  GLint status{};
  glGetProgramiv(program_, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    auto log = getProgramLog(program_);
    glDeleteProgram(program_);
    LOG_THROW(std::logic_error, log);
  }
}

Program::~Program() {
  LOG_TRACE << "GL::Program: destructor";

  if (program_) {
    glDetachShader(program_, fragmentShader_);
    glDetachShader(program_, vertexShader_);

    glDeleteShader(fragmentShader_);
    glDeleteShader(vertexShader_);
    glDeleteProgram(program_);
  }
}

bool Program::use() {
  glUseProgram(program_);
  if (glGetError() != GL_NO_ERROR) {
    LOG_WARNING << "gl_error: program can not be used";
    return false;
  }
  return true;
}

Program::Program(Program &&rhs)
    : program_{rhs.program_}
    , vertexShader_{rhs.vertexShader_}
    , fragmentShader_{rhs.fragmentShader_} {
  LOG_DEBUG << "GL::Program moved";

  rhs.program_        = 0;
  rhs.vertexShader_   = 0;
  rhs.fragmentShader_ = 0;
}

Program &Program::operator=(Program &&rhs) {
  LOG_DEBUG << "GL::Program moved";

  if (program_) {
    glDetachShader(program_, fragmentShader_);
    glDetachShader(program_, vertexShader_);

    glDeleteShader(fragmentShader_);
    glDeleteShader(vertexShader_);
    glDeleteProgram(program_);
  }

  program_        = rhs.program_;
  vertexShader_   = rhs.vertexShader_;
  fragmentShader_ = rhs.fragmentShader_;

  rhs.program_        = 0;
  rhs.vertexShader_   = 0;
  rhs.fragmentShader_ = 0;

  return *this;
}

int Program::getUniformLocation(std::string_view name) const {
  return ::glGetUniformLocation(program_, std::string{name}.c_str());
}
} // namespace KaliLaska::GL
