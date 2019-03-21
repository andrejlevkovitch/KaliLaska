// WindowGL.cpp

#include "WindowGL.hpp"
#include <GL/gl3w.h>
#include <iostream>
#include <random>

#define GL_CHECK()                                                             \
  {                                                                            \
    if (glGetError()) {                                                        \
      std::cerr << __LINE__ << std::endl;                                      \
      throw std::runtime_error{"opengl error"};                                \
    }                                                                          \
  }

static std::string vertexShader{R"(
#version 300 es
in vec2 pos;
in vec3 color;
out vec4 outColor;

void main() {
  gl_Position = vec4(pos, 0, 1);
  outColor = vec4(color, 1);
}
)"};

static std::string fragmentShader{R"(
#version 300 es
#ifdef GL_ES
precision highp float;
#endif
in vec4 outColor;
out vec4 fragColor;

void main() {
  fragColor = outColor;
}
)"};

WindowGL::WindowGL(const char *title, KaliLaska::Size size)
    : Window{title, size}
    , shaderProgram_{}
    , vertexShader_{}
    , fragmentShader_{} {
  // create shader program
  gl3wInit();
  std::cerr << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  shaderProgram_ = glCreateProgram();
  GL_CHECK();

  // create shaders
  vertexShader_ = glCreateShader(GL_VERTEX_SHADER);
  GL_CHECK();
  fragmentShader_ = glCreateShader(GL_FRAGMENT_SHADER);
  GL_CHECK();

  // compile shaders
  GLint status{};
  auto  code = &vertexShader[0];
  glShaderSource(vertexShader_, 1, &code, nullptr);
  GL_CHECK();
  glCompileShader(vertexShader_);
  GL_CHECK();
  glGetShaderiv(vertexShader_, GL_COMPILE_STATUS, &status);
  if (!status) {
    throw std::runtime_error{"compile error vertex shader"};
  }

  code = &fragmentShader[0];
  glShaderSource(fragmentShader_, 1, &code, nullptr);
  GL_CHECK();
  glCompileShader(fragmentShader_);
  GL_CHECK();
  glGetShaderiv(fragmentShader_, GL_COMPILE_STATUS, &status);
  if (!status) {
    throw std::runtime_error{"compile error fragment shader"};
  }

  // attach shaders
  glAttachShader(shaderProgram_, vertexShader_);
  GL_CHECK();
  glAttachShader(shaderProgram_, fragmentShader_);
  GL_CHECK();

  // set attrib locations
  glBindAttribLocation(shaderProgram_, 0, "pos");
  GL_CHECK();
  glBindAttribLocation(shaderProgram_, 1, "color");
  GL_CHECK();

  // set using program
  glLinkProgram(shaderProgram_);
  GL_CHECK();
  glGetProgramiv(shaderProgram_, GL_LINK_STATUS, &status);
  if (!status) {
    throw std::runtime_error{"link not complete"};
  }
  glValidateProgram(shaderProgram_);
  GL_CHECK();
  glUseProgram(shaderProgram_);
  GL_CHECK();
}

WindowGL::~WindowGL() {
  glDeleteShader(vertexShader_);
  glDeleteShader(fragmentShader_);
  glDeleteProgram(shaderProgram_);
}

void WindowGL::update() {
  auto now = std::chrono::system_clock::now();
  if (auto duration = now - last_; duration >= std::chrono::milliseconds{300}) {
    Window::makeCurrent();

    std::random_device                    rd{};
    std::default_random_engine            engine{rd()};
    std::uniform_real_distribution<float> colorDistrib{0, 1};
    std::uniform_real_distribution<float> vertexDistrib{-1, 1};

    glViewport(0, 0, drawSize().width(), drawSize().height());
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    float verticies[15]{
        vertexDistrib(engine),
        vertexDistrib(engine),
        colorDistrib(engine),
        colorDistrib(engine),
        colorDistrib(engine),
        vertexDistrib(engine),
        vertexDistrib(engine),
        colorDistrib(engine),
        colorDistrib(engine),
        colorDistrib(engine),
        vertexDistrib(engine),
        vertexDistrib(engine),
        colorDistrib(engine),
        colorDistrib(engine),
        colorDistrib(engine),
    };
    int elements[3]{0, 1, 2};

    GLuint vbo{};
    GLuint ebo{};

    glGenBuffers(1, &vbo);
    GL_CHECK();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GL_CHECK();
    glBufferData(
        GL_ARRAY_BUFFER, 15 * sizeof(float), verticies, GL_STATIC_DRAW);
    GL_CHECK();

    glGenBuffers(1, &ebo);
    GL_CHECK();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    GL_CHECK();
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(int), elements, GL_STATIC_DRAW);
    GL_CHECK();

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    GL_CHECK();
    glEnableVertexAttribArray(0);
    GL_CHECK();
    glVertexAttribPointer(1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          5 * sizeof(float),
                          reinterpret_cast<void *>(2 * sizeof(float)));
    GL_CHECK();
    glEnableVertexAttribArray(1);
    GL_CHECK();

    glDrawElements(GL_TRIANGLES, sizeof(elements), GL_UNSIGNED_INT, nullptr);
    GL_CHECK();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);

    swapWindow();

    last_ = std::chrono::system_clock::now();
  } else {
    std::cerr << std::chrono::duration_cast<std::chrono::milliseconds>(duration)
                     .count()
              << std::endl;
  }
}
