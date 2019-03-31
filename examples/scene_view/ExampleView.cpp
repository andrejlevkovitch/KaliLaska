// ExampleView.cpp

#include "ExampleView.hpp"
#include "KaliLaska/GraphicsItem.hpp"
#include "KaliLaska/GraphicsScene.hpp"
#include "KaliLaska/MouseFocusEvent.hpp"
#include "KaliLaska/MouseMoveEvent.hpp"
#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/MouseReleaseEvent.hpp"
#include "KaliLaska/MouseWheelEvent.hpp"
#include <GL/gl3w.h>
#include <boost/geometry.hpp>
#include <iostream>

#define SCALE_VAL 0.1

namespace bg = boost::geometry;
namespace bq = boost::qvm;

static std::string vertexShader{R"(
#version 300 es
uniform vec2 win_size;
uniform vec2 win_pos;
in vec2 pos;
in vec3 color;
out vec4 outColor;

void main() {
  mat4 to_view_pos = mat4(
    1,          0,          0, 0,
    0,          1,          0, 0,
    0,          0,          1, 0,
    -win_pos.x, -win_pos.y, 0, 1
  );
  mat4 to_ndc = mat4(
    2.0 / win_size.x, 0,                 0, 0,
    0,                -2.0 / win_size.y, 0, 0,
    0,                0,                 1, 0,
    -1,               1,                 0, 1
  );

  gl_Position = to_ndc * to_view_pos * vec4(pos, 1, 1);
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

ExampleView::ExampleView(std::string_view        title,
                         const KaliLaska::Point &pos,
                         const KaliLaska::Size & size)
    : GraphicsView{title, pos, size}
    , prog_{vertexShader, fragmentShader} {
  prog_.use();

  setProperty(Property::Movable);
}

void ExampleView::setScene(KaliLaska::GraphicsScene *scene) {
  GraphicsView::setScene(scene);
}

void ExampleView::mouseWheelEvent(
    std::unique_ptr<KaliLaska::MouseWheelEvent> event) {
  auto &mat = matrix();
  switch (event->scale()) {
  case KaliLaska::Mouse::Scale::ScaleDown:
    bq::mat_traits<KaliLaska::TransformMatrix>::write_element<0, 0>(mat) +=
        SCALE_VAL;
    bq::mat_traits<KaliLaska::TransformMatrix>::write_element<1, 1>(mat) +=
        SCALE_VAL;

    break;
  case KaliLaska::Mouse::Scale::ScaleUp:
    bq::mat_traits<KaliLaska::TransformMatrix>::write_element<0, 0>(mat) -=
        SCALE_VAL;
    bq::mat_traits<KaliLaska::TransformMatrix>::write_element<1, 1>(mat) -=
        SCALE_VAL;

    break;
  default:
    break;
  }
}

void ExampleView::update() {
  if (scene()) {
    auto now = std::chrono::system_clock::now();
    if (auto duration = now - last_;
        duration >= std::chrono::milliseconds{30}) {
      Window::makeCurrent();

      auto curSceneBox = sceneBox();

      glViewport(0, 0, drawSize().width(), drawSize().height());
      glClearColor(0, 0, 0, 1);
      glClear(GL_COLOR_BUFFER_BIT);

      KaliLaska::PointF sceneSize = curSceneBox.max_corner();
      bg::subtract_point(sceneSize, curSceneBox.min_corner());
      glUniform2f(0, bg::get<0>(sceneSize), bg::get<1>(sceneSize));
      glUniform2f(1,
                  bg::get<0>(curSceneBox.min_corner()),
                  bg::get<1>(curSceneBox.min_corner()));
      for (const auto &i : scene()->itemsAt(sceneBox())) {
        i->render();
      }

      swapWindow();

      last_ = std::chrono::system_clock::now();
    }
  }
}
