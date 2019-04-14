// opengl.hpp

#pragma once

#include "KaliLaska/Box.hpp"
#include "KaliLaska/Color.hpp"
#include "KaliLaska/Ring.hpp"
#include "KaliLaska/Size.hpp"
#include "KaliLaska/TransformMatrix.hpp"
#include "kalilaska_export.h"
#include <list>
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

class Renderer;

class KALILASKA_EXPORT Program final {
public:
  /**\throw exception if shader or program can not be created
   * \warning after creation the program not in use! For use the program you
   * have to call use() method
   */
  Program(std::string_view vertesShaderCode,
          std::string_view fragmentShaderCode);
  ~Program();

  /**\return true if program in use, otherwise - false
   */
  bool use();

  Program(Program &&rhs);
  Program &operator=(Program &&rhs);

  Program(const Program &) = delete;
  Program &operator=(const Program &) = delete;

private:
  uint32_t program_;
  uint32_t vertexShader_;
  uint32_t fragmentShader_;
};

/**\brief 2D OpenGL renderer
 */
class KALILASKA_EXPORT Renderer final {
public:
  enum class Uniforms {
    /**\breif vec2 which describe window size. Uses for translate view
     * koordinates to ndc_koordinates
     */
    WinSize,

    /**\brief mat3 which uses for translate scene koordinates to view
     * koordinates
     */
    ViewMat,

    /**\brief mat3 which uses for transformation of item
     */
    ItemMat,

    /**\brief vec3 for color, which will be used for fill all geometry
     */
    FillColor,

    /**\brief after the value (ant the value also) user can use for add you
     * own uniform
     */
    UserUni = 50
  };

  enum class Attributes {
    /**\brief vec2 input vertex for gl_Position
     */
    Vertex,
    /**\brief vec3 input color for vertex
     */
    Color,
    /**\brief after the value (ant the value also) user can use for add you
     * own attribute
     */
    UserAttr = 50
  };

  /**\param box geometry for rendering
   * \param color that color will be used for filling of geometry (box)
   * \param mat transformation matrix (translate, scale, rotation)
   */
  void render(const Box &box, const Color &color, const TransformMatrix &mat);

  /**\param ring geometry for rendering
   * \param color that color will be used for filling of geometry (fing)
   * \param mat transformation matrix (translate, scale, rotation)
   */
  void render(const Ring &ring, const Color &color, const TransformMatrix &mat);

  /**\brief register program in Renderer, after the program can be used for use
   * by the name
   *
   * \param programName name of program, which will be use for get program
   *
   * \param program valid GL::Program
   */
  void registerProgram(std::string_view programName, GL::Program program);

  /**\breif remove the program from registered
   */
  void unRegisterProgram(std::string_view programName);

  /**\brief use the method for choise which registered GL::Program you want to
   * use for rendering
   *
   * \return true if program in use, false - otherwise
   * \param programName registered program name
   */
  bool use(std::string_view programName);

  /**\brief call glViewPort and set uniform WinSize to current program
   */
  void setWinSize(const Size &size);

  void setViewMat(const TransformMatrix &mat);

  void clear(const Color &clearColor);

private:
  std::list<std::pair<std::string, GL::Program>> programs_;
};
} // namespace KaliLaska::GL
