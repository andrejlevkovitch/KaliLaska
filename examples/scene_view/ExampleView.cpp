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
#include "KaliLaska/opengl.hpp"
#include "shaders.hpp"
#include <boost/qvm/mat_operations.hpp>
#include <fstream>
#include <iostream>

#define SCALE_VAL 1.1

namespace bg = boost::geometry;
namespace bq = boost::qvm;

ExampleView::ExampleView(std::string_view        title,
                         const KaliLaska::Point &pos,
                         const KaliLaska::Size & size)
    : GraphicsView{title, pos, size} {
  auto shaderCodeLoader = [](const std::filesystem::path &fileName) {
    std::string retval;
    if (!std::filesystem::exists(fileName) &&
        !std::filesystem::is_regular_file(fileName)) {
      throw std::runtime_error{"file not exists"};
    }
    std::ifstream fin;
    fin.open(std::string{fileName}, std::ios::in);
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

  std::string vertexShader      = shaderCodeLoader(vertexShaderFile);
  std::string fragmentShader    = shaderCodeLoader(fragmentShaderFile);
  std::string vertexTexShader   = shaderCodeLoader(vertexTexShaderFile);
  std::string fragmentTexShader = shaderCodeLoader(fragmentTexShaderFile);

  renderer()->registerProgram("default", {vertexShader, fragmentShader});
  renderer()->registerProgram("texture", {vertexTexShader, fragmentTexShader});

  if (!renderer()->use("default")) {
    std::runtime_error{"opengl program not valid"};
  }
  renderer()->setWinSize(drawSize());
  renderer()->blending(true);
}

ExampleView::~ExampleView() {
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
        duration >= std::chrono::milliseconds{50}) {
      Window::makeCurrent();

      renderer()->clear(KaliLaska::Color::Colors::Black);
      renderer()->setViewMat(bq::inverse(matrix()));

      constexpr auto comparator = [](const KaliLaska::GraphicsItem *lhs,
                                     const KaliLaska::GraphicsItem *rhs) {
        if (lhs->zvalue() > rhs->zvalue() ||
            (lhs->zvalue() == rhs->zvalue() && !lhs->isAbove(rhs))) {
          return true;
        }
        return false;
      };

      for (const auto i : scene()->itemsAt(sceneBox(), comparator)) {
        i->render(renderer());
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

void ExampleView::resizeEvent(std::unique_ptr<KaliLaska::ResizeEvent> event) {
  (void)event;
  makeCurrent();
  renderer()->setWinSize(drawSize());
}
