// opengl.hpp

#pragma once

#include "KaliLaska/Box.hpp"
#include "KaliLaska/Color.hpp"
#include "kalilaska_export.h"
#include <string>

/**\brief the macros check openGL errors, and throw runtime_error, when some
 * error happens
 */
#define GL_CHECK()                                                             \
  {                                                                            \
    std::string error__GL;                                                     \
    switch (glGetError()) {                                                    \
    case GL_NO_ERROR:                                                          \
      break;                                                                   \
    case GL_INVALID_ENUM:                                                      \
      error__GL = "gl_error: invalid enum\n";                                  \
      break;                                                                   \
    case GL_INVALID_VALUE:                                                     \
      error__GL = "gl_error: invalid value\n";                                 \
      break;                                                                   \
    case GL_INVALID_OPERATION:                                                 \
      error__GL = "gl_error: invalid operation\n";                             \
      break;                                                                   \
    case GL_INVALID_FRAMEBUFFER_OPERATION:                                     \
      error__GL = "gl_error: invalid framebuffer operation\n";                 \
      break;                                                                   \
    case GL_OUT_OF_MEMORY:                                                     \
      error__GL = "gl_error: out of memory\n";                                 \
      break;                                                                   \
    default:                                                                   \
      error__GL = "gl_error: unknown\n";                                       \
      break;                                                                   \
    }                                                                          \
    if (!error__GL.empty()) {                                                  \
      error__GL += __FILE__;                                                   \
      error__GL += ':';                                                        \
      error__GL += std::to_string(__LINE__);                                   \
      error__GL += ' ';                                                        \
      error__GL += __FUNCTION__;                                               \
      throw std::runtime_error{error__GL};                                     \
    }                                                                          \
  }

namespace KaliLaska::GL {
class GLFactory;
class Shader;

class KALILASKA_EXPORT ShaderProgram final {
public:
  /**\throw runtime_exception if shader or program can not be created
   */
  ShaderProgram(std::string_view vertesShaderCode,
                std::string_view fragmentShaderCode);
  ~ShaderProgram();

  /**\throw runtime_exception if can not use current program
   */
  void use();

  ShaderProgram(ShaderProgram &&rhs);
  ShaderProgram &operator=(ShaderProgram &&rhs);

  ShaderProgram(const ShaderProgram &) = delete;
  ShaderProgram &operator=(const ShaderProgram &) = delete;

private:
  uint32_t program_;
  uint32_t vertexShader_;
  uint32_t fragmentShader_;
};

/**\brief 2D OpenGL renderer
 */
class KALILASKA_EXPORT Renderer final {
public:
  static void render(const Box &box, const Color &color);
};
} // namespace KaliLaska::GL
