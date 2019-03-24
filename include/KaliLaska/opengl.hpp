// opengl.hpp

#pragma once

#include <string>

/**\brief the macros check openGL errors, and throw runtime_error, when some
 * error happens
 */
#define GL_CHECK()                                                             \
  {                                                                            \
    auto some_error = ::glGetError();                                          \
    if (some_error != GL_NO_ERROR) {                                           \
      std::string error__GL;                                                   \
      switch (some_error) {                                                    \
      case GL_INVALID_ENUM:                                                    \
        error__GL = "gl_error: invalid enum\n";                                \
        break;                                                                 \
      case GL_INVALID_VALUE:                                                   \
        error__GL = "gl_error: invalid value\n";                               \
        break;                                                                 \
      case GL_INVALID_OPERATION:                                               \
        error__GL = "gl_error: invalid operation\n";                           \
        break;                                                                 \
      case GL_INVALID_FRAMEBUFFER_OPERATION:                                   \
        error__GL = "gl_error: invalid framebuffer operation\n";               \
        break;                                                                 \
      case GL_OUT_OF_MEMORY:                                                   \
        error__GL = "gl_error: out of memory\n";                               \
        break;                                                                 \
      default:                                                                 \
        error__GL = "gl_error: unknown\n";                                     \
        break;                                                                 \
      }                                                                        \
      error__GL += __FILE__;                                                   \
      error__GL += ':';                                                        \
      error__GL += std::to_string(__LINE__);                                   \
      error__GL += ' ';                                                        \
      error__GL += __FUNCTION__;                                               \
      throw std::runtime_error{error__GL};                                     \
    }                                                                          \
  }

namespace KaliLaska {} // namespace KaliLaska
