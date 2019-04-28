// opengl.hpp

#pragma once

#include "KaliLaska/Box.hpp"
#include "KaliLaska/Color.hpp"
#include "KaliLaska/Ring.hpp"
#include "KaliLaska/Size.hpp"
#include "KaliLaska/TransformMatrix.hpp"
#include "kalilaska_export.h"
#include <map>
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

class Texture {
public:
};

// FIXME not working
class KALILASKA_EXPORT Cache final {
  friend Renderer;

public:
  /**\brief create not valid (void) cache
   */
  Cache();
  ~Cache();

  Cache(Cache &&rhs);
  Cache &operator=(Cache &&rhs);

  /**\param val if true - bind current vao, vbo and ebo, otherwise bind 0
   */
  void bind(bool val = true) const;

  Cache(const Cache &) = delete;
  Cache &operator=(const Cache &) = delete;

  /**\return true if Cache is valid, otherwise - false
   */
  operator bool() const;

private:
  /**\brief create valid cache. Using by Renderer
   */
  explicit Cache(uint32_t vertexCount);

private:
  uint32_t vao_;
  uint32_t vbo_;
  uint32_t ebo_;

  uint32_t vertexCount_;
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
    UserAttr = 8
  };

  /**\param box geometry for rendering
   * \param color that color will be used for filling of geometry (box)
   * \param mat transformation matrix (translate, scale, rotation)
   */
  void render(const Box &box, const TransformMatrix &mat, const Color &color);

  /**\param ring geometry for rendering
   * \param color that color will be used for filling of geometry (fing)
   * \param mat transformation matrix (translate, scale, rotation)
   */
  void render(const Ring &ring, const TransformMatrix &mat, const Color &color);

  /**\brief draw texture. itemRing and textureRing have to have equal size -
   * every vertex of item will be correlated with vertex in texture
   *
   * \param itemRing ring in which will be draw (in item koordinates)
   * \param textureRing ring of texture (in texture koordinates)
   * \param itemMat transformation matrix (translate, scale, rotation)
   */
  void render(const Ring &           itemRing,
              const TransformMatrix &itemMat,
              const Texture &        texture,
              const Ring &           textureRing);

  /**\brief draw Texture
   * \param itemRing drawable item ring in item koordinates
   * \param itemMat transformation matrix of GraphicItem
   * \param textureMat matrix, which translate item koordinates to texture
   * koordinates. If item koordinates and texture koordinates are equal or
   * evulation not needed, then you can not set the parameter
   */
  void render(const Ring &           itemRing,
              const TransformMatrix &itemMat,
              const Texture &        texture,
              const TransformMatrix &textureMat = TransformMatrix{
                  {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}});

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
  std::map<std::string, GL::Program> programs_;
};
} // namespace KaliLaska::GL
