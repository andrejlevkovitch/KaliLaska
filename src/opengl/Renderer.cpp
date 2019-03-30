// Renderer.cpp

#include "KaliLaska/opengl.hpp"
#include <GL/gl3w.h>
#include <boost/geometry.hpp>

namespace bg = boost::geometry;

namespace KaliLaska::GL {
void Renderer::render(const Box &box, const Color &color) {
  bg::model::ring<PointF> ring;
  bg::convert(box, ring);
  float vertexBuffer[20]{};
  for (int i{}; i < 4; ++i) {
    int j               = i * 5;
    vertexBuffer[j]     = bg::get<0>(ring[i]);
    vertexBuffer[j + 1] = bg::get<1>(ring[i]);
    vertexBuffer[j + 2] = color.r();
    vertexBuffer[j + 3] = color.g();
    vertexBuffer[j + 4] = color.b();
  }

  unsigned int elementBuffer[4]{1, 0, 2, 3};

  GLuint vbo{};
  GLuint ebo{};
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBufferData(
      GL_ARRAY_BUFFER, 20 * sizeof(float), vertexBuffer, GL_STATIC_DRAW);
  glBufferData(
      GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(int), elementBuffer, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
  glVertexAttribPointer(1,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        5 * sizeof(float),
                        reinterpret_cast<void *>((2 * sizeof(float))));

  glDrawElements(
      GL_TRIANGLE_STRIP, sizeof(elementBuffer), GL_UNSIGNED_INT, nullptr);

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
}
} // namespace KaliLaska::GL
