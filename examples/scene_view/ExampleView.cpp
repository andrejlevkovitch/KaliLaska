// ExampleView.cpp

#include "ExampleView.hpp"
#include "KaliLaska/AbstractGraphicsItem.hpp"
#include "KaliLaska/GraphicsScene.hpp"
#include "KaliLaska/KeyPressEvent.hpp"
#include "KaliLaska/Menu.hpp"
#include "KaliLaska/MouseFocusEvent.hpp"
#include "KaliLaska/MouseMoveEvent.hpp"
#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/MouseReleaseEvent.hpp"
#include "KaliLaska/MouseWheelEvent.hpp"
#include "KaliLaska/opengl.hpp"
#include "imgui.h"
#include "imgui_internal.h"
#include "shaders.hpp"
#include <boost/qvm/mat_operations.hpp>
#include <fstream>
#include <iostream>

#define SCALE_FACTORS                                                          \
  { 1.1, 1.1 }
#define REVERS_FACTORS                                                         \
  { 1 / 1.1, 1 / 1.1 }

namespace bg = boost::geometry;
namespace bq = boost::qvm;

ExampleView::ExampleView(std::string_view        title,
                         const KaliLaska::Point &pos,
                         const KaliLaska::Size & size)
    : AbstractGraphicsView{title, pos, size}
    , clearColor_{KaliLaska::Color::Colors::Black} {
  auto shaderCodeLoader = [](const std::filesystem::path &fileName) {
    std::string retval;
    if (!std::filesystem::exists(fileName) &&
        !std::filesystem::is_regular_file(fileName)) {
      throw std::runtime_error{"file not exists"};
    }
    std::ifstream fin;
    fin.open(fileName, std::ios::in);
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

  renderer()->registerProgram("default", {vertexShader, fragmentShader});

  if (!renderer()->use("default")) {
    std::runtime_error{"opengl program not valid"};
  }
  renderer()->setWinSize(drawSize());
  renderer()->blending(true);
}

ExampleView::~ExampleView() {
}

void ExampleView::mousePressEvent(
    std::unique_ptr<KaliLaska::MousePressEvent> event) {
  if ((event->buttons() & KaliLaska::Mouse::Button::Right)) {
    menu_                        = std::make_unique<KaliLaska::Menu>(*this);
    KaliLaska::PointF sceneKoord = mapToScene(event->clickPos());
    if (scene()) {
      if (auto itemUnderCursor = scene()->itemAt(sceneKoord)) {
        menu_->setImgui(itemUnderCursor->contextMenu());
        return;
      }
    }
    menu_->setImgui([this]() {
      auto       curMatrix = this->matrix();
      auto       tmpColor  = this->clearColor_;
      float      angle     = this->getRotation();
      auto       scale     = this->getScale();
      const auto prevScale = scale;
      const auto prevAngle = angle;

      ImGui::NewFrame();
      ImGui::Begin("View");
      ImGui::InputFloat2(
          "view anchor", reinterpret_cast<float *>(&this->anchor_), "%.0f");
      ImGui::SliderFloat2(
          "view scalse", reinterpret_cast<float *>(&scale), 0.1f, 10.f);
      ImGui::SliderAngle("view rotation", &angle);
      ImGui::Separator();
      ImGui::ColorEdit3("clear color", reinterpret_cast<float *>(&clearColor_));
      ImGui::Separator();
      // clang-format off
      ImGui::Text("ViewMatrix:\n%.3f %.3f %.3f\n%.3f %.3f %.3f\n%.3f %.3f %.3f",
                  curMatrix.a[0][0], curMatrix.a[0][1], curMatrix.a[0][2],
                  curMatrix.a[1][0], curMatrix.a[1][1], curMatrix.a[1][2],
                  curMatrix.a[2][0], curMatrix.a[2][1], curMatrix.a[2][2]);
      auto box = this->sceneBox();
      ImGui::Text("\nSceneSize: min(%.1f, %.1f) max(%.1f, %.1f)",
          bg::get<bg::min_corner, 0>(box),bg::get<bg::min_corner, 1>(box),
          bg::get<bg::max_corner, 0>(box),bg::get<bg::max_corner, 1>(box)
          );
      // clang-format on
      ImGui::Separator();
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                  1000.0f / ImGui::GetIO().Framerate,
                  ImGui::GetIO().Framerate);
      ImGui::End();
      ImGui::EndFrame();

      if (prevAngle != angle) {
        this->setRotation(angle, this->anchor_);
      }
      if (prevScale != scale) {
        this->setScale(scale, this->anchor_);
      }
      if (clearColor_ != tmpColor) {
        this->renderer()->setClearColor(clearColor_);
      }
    });
  } else {
    if (menu_) {
      menu_.reset();
    }
    KaliLaska::AbstractGraphicsView::mousePressEvent(std::move(event));
  }
}

void ExampleView::mouseWheelEvent(
    std::unique_ptr<KaliLaska::MouseWheelEvent> event) {
  switch (event->scale()) {
  case KaliLaska::Mouse::Scale::ScaleDown:
    scale(SCALE_FACTORS,
          KaliLaska::PointF(event->position().x(), event->position().y()));
    break;
  case KaliLaska::Mouse::Scale::ScaleUp:
    scale(REVERS_FACTORS,
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
      render();
      last_ = std::chrono::system_clock::now();
    }
  }
}

void ExampleView::keyPressEvent(
    std::unique_ptr<KaliLaska::KeyPressEvent> event) {
  switch (event->key()) {
  case KaliLaska::Keyboard::Key::Key_A:
    rotate(KaliLaska::toRad(5), anchor_);
    break;
  case KaliLaska::Keyboard::Key::Key_D:
    rotate(KaliLaska::toRad(-5), anchor_);
    break;
  default:
    break;
  }
  KaliLaska::AbstractGraphicsView::keyPressEvent(std::move(event));
}

void ExampleView::resizeEvent(std::unique_ptr<KaliLaska::ResizeEvent> event) {
  (void)event;
  makeCurrent();
  renderer()->setWinSize(drawSize());
}

void ExampleView::render() const {
  makeCurrent();

  renderer()->clear();
  // the matrix have to transform scene koordinates to view koordinates
  renderer()->setViewMat(bq::inverse(matrix()));

  constexpr auto comparator = [](const KaliLaska::AbstractGraphicsItem *lhs,
                                 const KaliLaska::AbstractGraphicsItem *rhs) {
    if (lhs->zvalue() > rhs->zvalue() ||
        (lhs->zvalue() == rhs->zvalue() && !lhs->isAbove(rhs))) {
      return true;
    }
    return false;
  };

  for (const auto i : scene()->itemsAt(sceneBox(), comparator)) {
    i->render(renderer());
  }

  if (menu_) {
    menu_->render();
  }
  swapWindow();
}
