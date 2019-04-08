// ExampleView.cpp

#include "ExampleView.hpp"
#include "KaliLaska/GraphicsItem.hpp"
#include "KaliLaska/GraphicsScene.hpp"
#include "KaliLaska/KeyPressEvent.hpp"
#include "KaliLaska/MouseFocusEvent.hpp"
#include "KaliLaska/MouseMoveEvent.hpp"
#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/MouseReleaseEvent.hpp"
#include "KaliLaska/MouseWheelEvent.hpp"
#include "shaders.hpp"
#include <GL/gl3w.h>
#include <boost/qvm/mat_operations.hpp>
#include <fstream>
#include <iostream>

#define SCALE_VAL 1.1

namespace bg = boost::geometry;
namespace bq = boost::qvm;

ExampleView::ExampleView(std::string_view        title,
                         const KaliLaska::Point &pos,
                         const KaliLaska::Size & size)
    : GraphicsView{title, pos, size}
    , prog_{} {
  auto shaderCodeLoader = [](std::string_view fileName) {
    std::string   retval;
    std::ifstream fin;
    fin.open(std::string{fileName}.c_str(), std::ios::in);
    if (fin.is_open()) {
      std::copy(std::istreambuf_iterator<char>(fin),
                std::istreambuf_iterator<char>(),
                std::back_inserter(retval));
      fin.close();
    } else {
      throw std::runtime_error{"file with shader can not be opened"};
    }
    return retval;
  };

  std::string vertexShader   = shaderCodeLoader(vertexShaderFile);
  std::string fragmentShader = shaderCodeLoader(fragmentShaderFile);

  prog_ = std::make_unique<KaliLaska::GL::ShaderProgram>(vertexShader,
                                                         fragmentShader);

  prog_->use();
}

void ExampleView::setScene(KaliLaska::GraphicsScene *scene) {
  GraphicsView::setScene(scene);
}

void ExampleView::mouseWheelEvent(
    std::unique_ptr<KaliLaska::MouseWheelEvent> event) {
  switch (event->scale()) {
  case KaliLaska::Mouse::Scale::ScaleDown:
    scale(SCALE_VAL,
          SCALE_VAL,
          KaliLaska::PointF(event->position().x(), event->position().y()));
    break;
  case KaliLaska::Mouse::Scale::ScaleUp:
    scale(1 / SCALE_VAL,
          1 / SCALE_VAL,
          KaliLaska::PointF(event->position().x(), event->position().y()));
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

      auto curDrawSize = drawSize();
      glViewport(0, 0, curDrawSize.width(), curDrawSize.height());
      glClearColor(0, 0, 0, 1);
      glClear(GL_COLOR_BUFFER_BIT);

      glUniform2f(0, curDrawSize.width(), curDrawSize.height());
      glUniformMatrix3fv(1, 1, true, bq::inverse(matrix()).a[0]);

      for (const auto i : scene()->itemsAt(sceneBox())) {
        glUniformMatrix3fv(2, 1, true, i->matrix().a[0]);
        i->render();
      }

      swapWindow();

      last_ = std::chrono::system_clock::now();
    }
  }
}

void ExampleView::keyPressEvent(
    std::unique_ptr<KaliLaska::KeyPressEvent> event) {
  auto curSize = drawSize();
  switch (event->key()) {
  case KaliLaska::Keyboard::Key::Key_A:
    rotate(5, {curSize.width() / 2.f, curSize.height() / 2.f});
    break;
  case KaliLaska::Keyboard::Key::Key_D:
    rotate(-5, {curSize.width() / 2.f, curSize.height() / 2.f});
    break;
  default:
    break;
  }
  KaliLaska::GraphicsView::keyPressEvent(std::move(event));
}
