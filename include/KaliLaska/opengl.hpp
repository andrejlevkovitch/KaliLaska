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

namespace KaliLaska {
class Picture;
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

  int getUniformLocation(std::string_view name) const;

  Program(Program &&rhs);
  Program &operator=(Program &&rhs);

  Program(const Program &) = delete;
  Program &operator=(const Program &) = delete;

private:
  uint32_t program_;
  uint32_t vertexShader_;
  uint32_t fragmentShader_;
};

class Texture final {
public:
  /**\brief load all picture to texture.
   * \warning After creation the texture is not binded!
   */
  explicit Texture(const Picture &fromRGBA32);
  ~Texture();

  Texture(Texture &&rhs);
  Texture &operator=(Texture &&rhs);

  Texture(const Texture &) = delete;
  Texture &operator=(const Texture &) = delete;

  /**\brief bind current texture. If you set false - bind 0
   */
  void bind(bool val = true) const;

private:
  uint32_t glTexture_;
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

// FIXME here is serious problem: we can not return cache, because it only for
// one context. So we can not draw it on other window
/**\brief 2D OpenGL renderer
 */
class KALILASKA_EXPORT Renderer final {
public:
  static inline std::string_view winSizeUniform{"win_size"};
  static inline std::string_view viewMatUniform{"view_mat"};
  static inline std::string_view itemMatUniform{"item_mat"};
  static inline std::string_view texture0Uniform{"texture0"};

  enum class Attributes {
    /**\brief vec2 input vertex for gl_Position
     */
    Vertex,
    /**\brief vec3 input color for vertex
     */
    Color,
    TexVertex,
    /**\brief after the value (ant the value also) user can use for add you
     * own attribute
     */
    UserAttr = 8
  };

  /**\param box geometry for rendering
   * \param color that color will be used for filling of geometry (box)
   * \param mat transformation matrix (translate, scale, rotation)
   */
  Cache render(const Box &box, const TransformMatrix &mat, const Color &color);

  /**\param ring geometry for rendering
   * \param color that color will be used for filling of geometry (fing)
   * \param mat transformation matrix (translate, scale, rotation)
   */
  Cache
  render(const Ring &ring, const TransformMatrix &mat, const Color &color);

  void
  render(const Cache &cache, const TransformMatrix &mat, const Color &color);

  /**\brief draw texture. itemRing and textureRing have to have equal size -
   * every vertex of item will be correlated with vertex in texture
   *
   * \param itemRing ring in which will be draw (in item koordinates)
   * \param textureRing ring of texture (in texture koordinates)
   * \param itemMat transformation matrix (translate, scale, rotation)
   */
  Cache render(const Ring &           itemRing,
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

  void render(const Cache &          cache,
              const TransformMatrix &itemMat,
              const Texture &        texture);

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
   * use for rendering. If you set empty string, then will be called 0 program
   *
   * \return true if program in use, false - otherwise. If you set empty string,
   * also will be returned true
   *
   * \param programName registered program name
   */
  bool use(std::string_view programName);

  /**\brief call glViewPort and set uniform WinSize to current program. This
   * uses for all registered programs
   * \warning if you set program after calling the method, then program can not
   * have the value, so use the method again in this case
   */
  void setWinSize(const Size &size);

  /**\brief set uniform ViewMat to current program. This uses for all registered
   * programs
   * \warning if you set program after calling the method, then program can not
   * have the value, so use the method again in this case
   */
  void setViewMat(const TransformMatrix &mat);

  /**\brief call glClearColor and glClear
   */
  void clear(const Color &clearColor);

  /**\return empty string if current program not set
   */
  std::string_view currentProgram() const;

private:
  std::map<std::string, GL::Program> programs_;
  std::string                        currentProgram_;
};
} // namespace KaliLaska::GL
