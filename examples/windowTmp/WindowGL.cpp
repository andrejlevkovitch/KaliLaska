// WindowGL.cpp

#include "WindowGL.hpp"
#include "KaliLaska/opengl.hpp"
#include <GL/gl3w.h>
#include <iostream>

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

using KaliLaska::GL::GLFactory;

WindowGL::WindowGL(std::string_view title, const KaliLaska::Size &size)
    : Window{title, size}
    , shaderProgram_{vertexShader, fragmentShader} {
  shaderProgram_.use();

  std::cerr << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

WindowGL::~WindowGL() {
}

void WindowGL::update() {
  auto now = std::chrono::system_clock::now();
  if (auto duration = now - last_; duration >= std::chrono::milliseconds{500}) {
    Window::makeCurrent();

    glViewport(0, 0, drawSize().width(), drawSize().height());
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    KaliLaska::GL::Renderer::render(
        KaliLaska::Box{KaliLaska::PointF{0.9, 0.9},
                       KaliLaska::PointF{-0.9, -0.9}},
        KaliLaska::Color{1, 0, 1});

    swapWindow();

    last_ = std::chrono::system_clock::now();
  }
}
