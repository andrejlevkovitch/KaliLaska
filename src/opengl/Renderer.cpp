// Renderer.cpp

#include "KaliLaska/opengl.hpp"
#include "debug.hpp"
#include <GLES3/gl3.h>
#include <boost/geometry.hpp>
#include <cstdint>

namespace bg = boost::geometry;

namespace KaliLaska::GL {
Renderer::Renderer() {
}

void Renderer::blending(bool val) {
  if (val) {
    ::glEnable(GL_BLEND);
    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  } else {
    ::glDisable(GL_BLEND);
  }
}

void Renderer::registerProgram(std::string_view programName,
                               GL::Program      program) {
  // you can not register empty string
  if (programName.empty()) {
    return;
  }
  programs_.emplace(programName, std::move(program));
}

void Renderer::unRegisterProgram(std::string_view programName) {
  if (auto found = programs_.find(std::string{programName});
      found != programs_.end()) {
    if (found->first == currentProgram_) {
      currentProgram_.clear();
    }
    programs_.erase(found);
  }
}

bool Renderer::use(std::string_view programName) {
  if (programName.empty()) {
    glUseProgram(0);
    currentProgram_.clear();
    return true;
  }
  if (auto found = programs_.find(std::string{programName});
      found != programs_.end()) {
    if (found->second.use()) {
      currentProgram_ = found->first;
      return true;
    }
  }
  return false;
}

Cache Renderer::render(const Box &            box,
                       const TransformMatrix &mat,
                       const Color &          color) {
  Cache retval{GL_TRIANGLE_STRIP, 4};

  if (auto found = programs_.find(currentProgram_); found != programs_.end()) {
    ::glUniformMatrix3fv(
        found->second.getUniformLocation(itemMatUniform), 1, true, mat.a[0]);
  }
  glVertexAttrib3fv(static_cast<int>(Attributes::Color),
                    reinterpret_cast<const float *>(&color));

  Ring ring;
  bg::convert(box, ring);
  static const std::array<uint16_t, 4> elementBuffer{1, 0, 2, 3};

  retval.bind(true);

  glBufferData(GL_ARRAY_BUFFER,
               (ring.size() - 1) * 2 * sizeof(float),
               ring.data(),
               GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               elementBuffer.size() *
                   sizeof(decltype(elementBuffer)::value_type),
               elementBuffer.data(),
               GL_STATIC_DRAW);

  glEnableVertexAttribArray(static_cast<int>(Attributes::Vertex));

  glVertexAttribPointer(
      static_cast<int>(Attributes::Vertex), 2, GL_FLOAT, GL_FALSE, 0, nullptr);

  glDrawElements(
      GL_TRIANGLE_STRIP, elementBuffer.size(), GL_UNSIGNED_SHORT, nullptr);

  glDisableVertexAttribArray(static_cast<int>(Attributes::Vertex));
  retval.bind(false);

  return retval;
}

Cache Renderer::render(const Ring &           ring,
                       const TransformMatrix &mat,
                       const Color &          color) {
  if (auto triangles = triangulation(ring); !triangles.empty()) {
    Cache retval(GL_TRIANGLES, triangles.size());

    if (auto found = programs_.find(currentProgram_);
        found != programs_.end()) {
      ::glUniformMatrix3fv(
          found->second.getUniformLocation(itemMatUniform), 1, true, mat.a[0]);
    }
    glVertexAttrib3fv(static_cast<int>(Attributes::Color),
                      reinterpret_cast<const float *>(&color));

    retval.bind(true);

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
                          0,
                          nullptr);

    glEnableVertexAttribArray(static_cast<int>(Attributes::Vertex));

    glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_SHORT, nullptr);

    glDisableVertexAttribArray(static_cast<int>(Attributes::Vertex));
    retval.bind(false);

    return retval;
  }

  return {};
}

void Renderer::render(const Cache &          cache,
                      const TransformMatrix &itemMat,
                      const Color &          color) {
  if (cache) {
    if (auto found = programs_.find(currentProgram_);
        found != programs_.end()) {
      ::glUniformMatrix3fv(found->second.getUniformLocation(itemMatUniform),
                           1,
                           true,
                           itemMat.a[0]);
    }
    glVertexAttrib3fv(static_cast<int>(Attributes::Color),
                      reinterpret_cast<const float *>(&color));

    cache.bind(true);
    glEnableVertexAttribArray(static_cast<int>(Attributes::Vertex));

    glDrawElements(
        cache.trianglesType_, cache.vertexCount_, GL_UNSIGNED_SHORT, nullptr);

    glDisableVertexAttribArray(static_cast<int>(Attributes::Vertex));
    cache.bind(false);
  }
}

Cache Renderer::render(const Ring &           itemRing,
                       const TransformMatrix &itemMat,
                       const Texture &        texture,
                       const Ring &           textureRing) {
  if (auto triangles = triangulation(itemRing); !triangles.empty()) {
    Cache retval(GL_TRIANGLES, triangles.size());

    if (auto found = programs_.find(currentProgram_);
        found != programs_.end()) {
      ::glUniformMatrix3fv(found->second.getUniformLocation(itemMatUniform),
                           1,
                           true,
                           itemMat.a[0]);
      ::glUniform1i(found->second.getUniformLocation(texture0Uniform), 0);
    }

    retval.bind(true);

    Ring verticies;
    verticies.reserve(itemRing.size() * 2);
    for (auto i = itemRing.begin(), j = textureRing.begin();
         i != itemRing.end() && j != textureRing.end();
         ++i, ++j) {
      verticies.push_back(*i);
      verticies.push_back(*j);
    }

    glBufferData(GL_ARRAY_BUFFER,
                 (verticies.size() - 2) * 2 * sizeof(float),
                 verticies.data(),
                 GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 triangles.size() * sizeof(decltype(triangles)::value_type),
                 triangles.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(static_cast<int>(Attributes::Vertex),
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          16,
                          nullptr);
    glEnableVertexAttribArray(static_cast<int>(Attributes::Vertex));

    glVertexAttribPointer(static_cast<int>(Attributes::TexVertex),
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          16,
                          reinterpret_cast<void *>(8));
    glEnableVertexAttribArray(static_cast<int>(Attributes::TexVertex));

    ::glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_SHORT, nullptr);

    texture.bind(false);

    glDisableVertexAttribArray(static_cast<int>(Attributes::TexVertex));
    glDisableVertexAttribArray(static_cast<int>(Attributes::Vertex));
    retval.bind(false);

    return retval;
  }
  return {};
}

void Renderer::render(const Cache &          cache,
                      const TransformMatrix &itemMat,
                      const Texture &        texture) {
  if (cache) {
    if (auto found = programs_.find(currentProgram_);
        found != programs_.end()) {
      ::glUniformMatrix3fv(
          found->second.getUniformLocation("item_mat"), 1, true, itemMat.a[0]);
      ::glUniform1i(found->second.getUniformLocation("texture0"), 0);
    }
    cache.bind(true);
    glEnableVertexAttribArray(static_cast<int>(Attributes::Vertex));
    glEnableVertexAttribArray(static_cast<int>(Attributes::TexVertex));
    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glDrawElements(
        cache.trianglesType_, cache.vertexCount_, GL_UNSIGNED_SHORT, nullptr);

    texture.bind(false);
    glDisableVertexAttribArray(static_cast<int>(Attributes::Vertex));
    glDisableVertexAttribArray(static_cast<int>(Attributes::TexVertex));
    cache.bind(false);
  }
}

void Renderer::setViewMat(const TransformMatrix &mat) {
  auto saved = currentProgram_;
  for (auto &[name, program] : programs_) {
    use(name);
    glUniformMatrix3fv(
        program.getUniformLocation(viewMatUniform), 1, true, mat.a[0]);
  }
  use(saved);
}

void Renderer::setWinSize(const Size &size) {
  glViewport(0, 0, size.width(), size.height());
  auto saved = currentProgram_;
  for (auto &[name, program] : programs_) {
    use(name);
    glUniform2f(program.getUniformLocation(winSizeUniform),
                size.width(),
                size.height());
  }
  use(saved);
}

void Renderer::setClearColor(const Color &clearColor) {
  auto saved = currentProgram_;
  for (auto &[name, program] : programs_) {
    use(name);
    glClearColor(
        clearColor.r(), clearColor.g(), clearColor.b(), clearColor.a());
  }
  use(saved);
}

void Renderer::clear() {
  glClear(GL_COLOR_BUFFER_BIT);
}
} // namespace KaliLaska::GL
