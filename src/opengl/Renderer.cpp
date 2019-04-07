// Renderer.cpp

#include "KaliLaska/opengl.hpp"
#include "debug.hpp"
#include <GL/gl3w.h>
#include <boost/geometry.hpp>

namespace bg = boost::geometry;

namespace KaliLaska::GL {
void Renderer::render(const Box &box, const Color &color) {
  glUniform3f(3, color.r(), color.g(), color.b());

  bg::model::ring<PointF> ring;
  bg::convert(box, ring);
  static const std::array<ushort, 4> elementBuffer{1, 0, 2, 3};

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

void Renderer::render(const Ring &ring, const Color &color) {
  glUniform3f(3, color.r(), color.g(), color.b());

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

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_SHORT, nullptr);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
  }
}
} // namespace KaliLaska::GL
