// WindowGL.cpp

#include "WindowGL.hpp"
#include "KaliLaska/opengl.hpp"
#include <GL/gl3w.h>
#include <iostream>
#include <random>

static std::string_view vertexShader{R"(
#version 300 es
in vec2 pos;
in vec3 color;
out vec4 outColor;

void main() {
  gl_Position = vec4(pos, 0, 1);
  outColor = vec4(color, 1);
}
)"};

static std::string_view fragmentShader{R"(
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

using KaliLaska::GL::GLFactory;

WindowGL::WindowGL(std::string_view title, const KaliLaska::Size &size)
    : Window{title, size} {
  GL_CHECK();
  renderer()->registerProgram(
      "default", KaliLaska::GL::Program{vertexShader, fragmentShader});
  GL_CHECK();
  if (!renderer()->use("default")) {
    throw std::runtime_error{"not valid GL::Program"};
  }
  GL_CHECK();
  glViewport(0, 0, drawSize().width(), drawSize().height());
  GL_CHECK();
}

WindowGL::~WindowGL() {
}

void WindowGL::update() {
  auto now = std::chrono::system_clock::now();
  if (auto duration = now - last_; duration >= std::chrono::milliseconds{500}) {
    Window::makeCurrent();

    std::random_device                    rd{};
    std::default_random_engine            engine{rd()};
    std::uniform_real_distribution<float> colorDistrib{0, 1};
    std::uniform_real_distribution<float> vertexDistrib{-1, 1};

    GL_CHECK();
    renderer()->clear(KaliLaska::Color::Colors::Black);
    GL_CHECK();

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
