// Cache.cpp

#include "KaliLaska/opengl.hpp"
#include <GLES3/gl3.h>

namespace KaliLaska::GL {
Cache::Cache()
    : vao_{}
    , vbo_{}
    , ebo_{}
    , vertexCount_{} {
}

Cache::Cache(uint32_t vertexCount)
    : vao_{}
    , vbo_{}
    , ebo_{}
    , vertexCount_{vertexCount} {
  ::glGenVertexArrays(1, &vao_);
  ::glGenBuffers(1, &vbo_);
  ::glGenBuffers(1, &ebo_);
}

Cache::~Cache() {
  if (vao_) {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
  }
}

Cache::Cache(Cache &&rhs)
    : vao_{rhs.vao_}
    , vbo_{rhs.vbo_}
    , ebo_{rhs.ebo_}
    , vertexCount_{rhs.vertexCount_} {
  rhs.vao_ = 0;
  rhs.vbo_ = 0;
  rhs.ebo_ = 0;
}

Cache &Cache::operator=(Cache &&rhs) {
  if (vao_) {
    ::glDeleteVertexArrays(1, &vao_);
    ::glDeleteBuffers(1, &vbo_);
    ::glDeleteBuffers(1, &ebo_);
  }

  vao_         = rhs.vao_;
  vbo_         = rhs.vbo_;
  ebo_         = rhs.ebo_;
  vertexCount_ = rhs.vertexCount_;
  rhs.vao_     = 0;
  rhs.vbo_     = 0;
  rhs.ebo_     = 0;

  return *this;
}

void Cache::bind(bool val) const {
  if (val) {
    ::glBindVertexArray(vao_);
    ::glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  } else {
    ::glBindVertexArray(0);
    ::glBindBuffer(GL_ARRAY_BUFFER, 0);
    ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
}

Cache::operator bool() const {
  return vao_;
}
} // namespace KaliLaska::GL
