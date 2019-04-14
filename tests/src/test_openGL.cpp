// test_openGL.cpp

#define CATCH_CONFIG_RUNNER
#include "KaliLaska/Application.hpp"
#include <catch2/catch.hpp>
int main(int argc, char *argv[]) {
  KaliLaska::Application app{argc, argv};
  int                    result = Catch::Session().run(argc, argv);
  return result;
}

#include "KaliLaska/Window.hpp"
#include "KaliLaska/opengl.hpp"
#include <GL/gl3w.h>

const std::string vertexShader{R"(
#version 300 es
in vec2 pos;
in vec3 color;
out vec4 outColor;

void main() {
  gl_Position = vec4(pos, 0, 1);
  outColor = vec4(color, 1);
}
)"};

const std::string fragmentShader{R"(
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

class OpenGLWindow : public KaliLaska::Window {
public:
  OpenGLWindow()
      : KaliLaska::Window{"", KaliLaska::Size{100, 100}} {
    renderer()->registerProgram("default", {vertexShader, fragmentShader});
    try {
      renderer()->use("default");
    } catch (const std::runtime_error &) {
      throw;
    }
  }

  ~OpenGLWindow() {}

  void update() {
    Window::makeCurrent();

    glViewport(0, 0, drawSize().width(), drawSize().height());
    renderer()->clear(KaliLaska::Color::Colors::Black);

    float verticies[15]{
        0.5, 0.5, 0, 0, 1, 0.0, 0.0, 0, 1, 0, -0.5, -0.4, 1, 0, 0};
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
  }
};
SCENARIO("Test openGL", "[OpenGLWindow]") {
  GIVEN("Application") {
    WHEN("We get window") {
      KaliLaska::Window *window{};

      REQUIRE_NOTHROW(window = new OpenGLWindow);

      THEN("Try update window") { REQUIRE_NOTHROW(window->update()); }
    }
  }
}
