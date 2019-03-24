// GLFactory.cpp

#include "KaliLaska/opengl.hpp"
#include <GL/gl3w.h>
#include <stdexcept>

namespace KaliLaska {
namespace GL {
Shader GLFactory::createShader(ShaderType type, std::string_view code) {
  uint32_t openglShader{};
  switch (type) {
  case ShaderType::Vertex:
    openglShader = glCreateShader(GL_VERTEX_SHADER);
    break;
  case ShaderType::Fragment:
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

  return Shader{openglShader};
}

Program GLFactory::createProgram() {
  uint32_t retval;
  retval = glCreateProgram();
  if (!retval) {
    throw std::runtime_error{"opengl program can not be created"};
  }
  return Program{retval};
}
} // namespace GL
} // namespace KaliLaska
