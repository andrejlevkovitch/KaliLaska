// opengl.hpp

#pragma once

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

namespace KaliLaska {
namespace GL {
class GLFactory;

/**\brief incapsulate shader object. In destructor destroy opengl shader object
 */
class KALILASKA_EXPORT Shader final {
  friend GLFactory;

public:
  ~Shader();

  Shader &operator=(Shader &&rhs);

  Shader(const Shader &) = delete;
  Shader &operator=(const Shader &) = delete;

  /**\return opengl shader object
   */
  uint32_t value() const;

private:
  explicit Shader(uint32_t openglShader);

private:
  uint32_t openglShader_;
};

class KALILASKA_EXPORT Program final {
  friend GLFactory;

public:
  ~Program();

  Program &operator=(Program &&rhs);

  Program(const Program &) = delete;
  Program &operator=(const Program &) = delete;

  /**\return opengl program object
   */
  uint32_t value() const;

private:
  explicit Program(uint32_t openglProgram);

private:
  uint32_t openglProgram_;
};

/**\brief attach shaders to program and link it in the konstructor and detach it
 * in destructor
 */
class KALILASKA_EXPORT Attacher final {
public:
  /**\throw runtime_error if some shader already attached
   */
  Attacher(const Program &program,
           const Shader & vertexShader,
           const Shader & fragmentShader);
  ~Attacher();

  Attacher &operator=(Attacher &&);

  Attacher(const Attacher &) = delete;
  Attacher &operator=(const Attacher &) = delete;

private:
  uint32_t program_;
  uint32_t vertexShader_;
  uint32_t fragmentShader_;
};

/**\brief factory for creating openGL objects
 */
class KALILASKA_EXPORT GLFactory final {
public:
  enum class ShaderType { Vertex, Fragment };

  /**\param code code of shader
   * \return opengl shader
   * \throw runtime_error if shader can not be compiled or if type is invalid
   */
  static Shader createShader(ShaderType type, std::string_view code);

  /**\return opengl program
   * \throw runtime_error if program can not be created
   */
  static Program createProgram();
};
} // namespace GL
} // namespace KaliLaska
