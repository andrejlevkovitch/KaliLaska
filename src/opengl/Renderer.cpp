// Renderer.cpp

#include "KaliLaska/opengl.hpp"
#include "debug.hpp"
#include <GL/gl3w.h>
#include <boost/geometry.hpp>
#include <cstdint>

namespace bg = boost::geometry;

namespace KaliLaska::GL {
void Renderer::registerProgram(std::string_view programName,
                               GL::Program      program) {
  programs_.push_back(std::pair{std::string(programName), std::move(program)});
}

void Renderer::unRegisterProgram(std::string_view programName) {
  if (auto found = std::find_if(programs_.begin(),
                                programs_.end(),
                                [&programName](const auto &val) {
                                  if (val.first == programName) {
                                    return true;
                                  }
                                  return false;
                                });
      found != programs_.end()) {
    programs_.erase(found);
  }
}

bool Renderer::use(std::string_view programName) {
  if (auto found = std::find_if(programs_.begin(),
                                programs_.end(),
                                [&programName](const auto &val) {
                                  if (val.first == programName) {
                                    return true;
                                  }
                                  return false;
                                });
      found != programs_.end()) {
    return found->second.use();
  }
  return false;
}

void Renderer::render(const Box &            box,
                      const Color &          color,
                      const TransformMatrix &mat) {
  glUniformMatrix3fv(static_cast<int>(Uniforms::ItemMat), 1, true, mat.a[0]);
  glUniform3f(
      static_cast<int>(Uniforms::FillColor), color.r(), color.g(), color.b());

  bg::model::ring<PointF> ring;
  bg::convert(box, ring);
  static const std::array<uint16_t, 4> elementBuffer{1, 0, 2, 3};

  GLuint vbo{};
  GLuint ebo{};
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBufferData(GL_ARRAY_BUFFER,
               (ring.size() - 1) * 2 * sizeof(float),
               ring.data(),
               GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               elementBuffer.size() *
                   sizeof(decltype(elementBuffer)::value_type),
               elementBuffer.data(),
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

  glDrawElements(
      GL_TRIANGLE_STRIP, elementBuffer.size(), GL_UNSIGNED_SHORT, nullptr);

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
}

void Renderer::render(const Ring &           ring,
                      const Color &          color,
                      const TransformMatrix &mat) {
  glUniformMatrix3fv(static_cast<int>(Uniforms::ItemMat), 1, true, mat.a[0]);
  glUniform3f(
      static_cast<int>(Uniforms::FillColor), color.r(), color.g(), color.b());

  if (auto triangles = triangulation(ring); !triangles.empty()) {
    GLuint vbo{};
    GLuint ebo{};
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBufferData(GL_ARRAY_BUFFER,
                 (ring.size() - 1) * 2 * sizeof(float),
                 ring.data(),
                 GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 triangles.size() * sizeof(decltype(triangles)::value_type),
                 triangles.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(static_cast<int>(Attributes::Vertex),
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          2 * sizeof(float),
                          nullptr);

    glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_SHORT, nullptr);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
  }
}

void Renderer::setViewMat(const TransformMatrix &mat) {
  glUniformMatrix3fv(static_cast<int>(Uniforms::ViewMat), 1, true, mat.a[0]);
}

void Renderer::setWinSize(const Size &size) {
  glViewport(0, 0, size.width(), size.height());
  glUniform2f(static_cast<int>(Uniforms::WinSize), size.width(), size.height());
}

void Renderer::clear(const Color &clearColor) {
  glClearColor(clearColor.r(), clearColor.g(), clearColor.b(), clearColor.a());
  glClear(GL_COLOR_BUFFER_BIT);
}
} // namespace KaliLaska::GL
