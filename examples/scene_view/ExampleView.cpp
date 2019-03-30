// ExampleView.cpp

#include "ExampleView.hpp"
#include "KaliLaska/GraphicsItem.hpp"
#include "KaliLaska/GraphicsScene.hpp"
#include "KaliLaska/MouseFocusEvent.hpp"
#include "KaliLaska/MouseMoveEvent.hpp"
#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/MouseReleaseEvent.hpp"
#include <GL/gl3w.h>
#include <boost/geometry.hpp>
#include <iostream>

namespace bg = boost::geometry;

static std::string vertexShader{R"(
#version 300 es
uniform vec2 win_size;
uniform vec2 win_pos;
in vec2 pos;
in vec3 color;
out vec4 outColor;

void main() {
  mat4 to_view_pos = mat4(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    -win_pos.x, -win_pos.y, 0, 1
  );
  mat4 to_ndc = mat4(2.0 / win_size.x, 0, 0, 0,
                     0, -2.0 / win_size.y, 0, 0,
                     0, 0, 1, 0,
                     -1, 1, 0, 1);

  vec4 temp_pos = to_view_pos * vec4(pos, 1, 1);
  gl_Position = to_ndc * temp_pos;
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
    , prog_{vertexShader, fragmentShader}
    , moveState_{false} {
  prog_.use();
}

void ExampleView::setScene(KaliLaska::GraphicsScene *scene) {
  GraphicsView::setScene(scene);
  this->setSceneBox(KaliLaska::Box{{0, 0}, {size().width(), size().height()}});
}

void ExampleView::mousePressEvent(
    std::unique_ptr<KaliLaska::MousePressEvent> event) {
  (void)event;
  moveState_ = true;
}

void ExampleView::mouseReleaseEvent(
    std::unique_ptr<KaliLaska::MouseReleaseEvent> event) {
  (void)event;
  moveState_ = false;
}

void ExampleView::mouseMoveEvent(
    std::unique_ptr<KaliLaska::MouseMoveEvent> event) {
  if (moveState_) {
    auto lastPos = event->previousPos();
    auto curPos  = event->currentPos();

    boost::geometry::subtract_point(curPos, lastPos);

    auto sceneRect = this->sceneBox();

    boost::geometry::strategy::transform::translate_transformer<float, 2, 2>
        translate(-curPos.x(), -curPos.y());

    boost::geometry::transform(sceneRect, sceneRect, translate);

    setSceneBox(sceneRect);
  }
}

void ExampleView::mouseFocusEvent(
    std::unique_ptr<KaliLaska::MouseFocusEvent> event) {
  if (event->focus() == KaliLaska::Mouse::Focus::Leave) {
    moveState_ = false;
  }
}

void ExampleView::update() {
  if (scene()) {
    auto now = std::chrono::system_clock::now();
    if (auto duration = now - last_;
        duration >= std::chrono::milliseconds{30}) {
      Window::makeCurrent();

      glViewport(0, 0, drawSize().width(), drawSize().height());
      glClearColor(0, 0, 0, 1);
      glClear(GL_COLOR_BUFFER_BIT);

      for (const auto &i : scene()->itemsAt(sceneBox())) {
        glUniform2f(0, size().width(), size().height());
        auto pos = sceneBox().min_corner();
        glUniform2f(1, bg::get<0>(pos), bg::get<1>(pos));
        i->render();
      }

      swapWindow();

      last_ = std::chrono::system_clock::now();
    }
  }
}
