// ExampleItem.cpp

#include "ExampleItem.hpp"
#include "ExampleScene.hpp"
#include "KaliLaska/GraphicsScene.hpp"
#include "KaliLaska/SceneMouseMoveEvent.hpp"
#include "KaliLaska/SceneMousePressEvent.hpp"
#include "KaliLaska/SceneMouseReleaseEvent.hpp"
#include "KaliLaska/opengl.hpp"
#include "imgui.h"
#include <iostream>

namespace bg = boost::geometry;

ExampleItem::ExampleItem(const KaliLaska::Color &color)
    : color_{color} {
  setAnchor({15, 15});
  setZvalue(1);
}

KaliLaska::Ring ExampleItem::shape() const {
  return {{0, 0}, {0, 30}, {30, 30}, {30, 0}, {0, 0}};
}

void ExampleItem::render(KaliLaska::GL::Renderer *renderer) const {
  if (cache_) {
    renderer->render(cache_, matrix(), color_);
  } else {
    cache_ = renderer->render(boundingBox(), matrix(), color_);
  }
}

void ExampleItem::update() {
  KaliLaska::PointF newPos = pos();
  bg::add_point(newPos, KaliLaska::PointF{0.5, 0.5});
  setPos(newPos);
}

void ExampleItem::mouseMoveEvent(KaliLaska::SceneMouseMoveEvent *event) {
  (void)event;
}

void ExampleItem::mousePressEvent(KaliLaska::SceneMousePressEvent *event) {
  scene()->grabbItem(this);
  event->accept();
  stackAbove();
}

void ExampleItem::mouseReleaseEvent(KaliLaska::SceneMouseReleaseEvent *event) {
  if (this == scene()->grabbedItem()) {
    scene()->grabbItem(nullptr);
    event->accept();
  }
}

KaliLaska::GraphicsItem::ItemType ExampleItem::type() const {
  return static_cast<KaliLaska::GraphicsItem::ItemType>(
      ExampleScene::ExampleItem);
}

std::function<void(void)> ExampleItem::contextMenu() {
  return [this]() {
    ImGui::NewFrame();
    ImGui::Begin("ExampleItem");

    auto       curMatrix = this->matrix();
    float      angle     = this->getRotation();
    auto       scale     = reinterpret_cast<GraphicsItem *>(this)->getScale();
    const auto prevScale = scale;
    const auto prevAngle = angle;

    ImGui::InputFloat2("item anchor", reinterpret_cast<float *>(&anchor_));
    ImGui::Separator();
    ImGui::SliderFloat2(
        "view scalse", reinterpret_cast<float *>(&scale), 0.1f, 10.f);
    ImGui::SliderAngle("view rotation", &angle);
    ImGui::Separator();
    ImGui::ColorEdit4("color of item",
                      reinterpret_cast<float *>(&this->color_));
    ImGui::Separator();
    // clang-format off
    ImGui::Text("ItemMatrix:\n%.3f %.3f %.3f\n%.3f %.3f %.3f\n%.3f %.3f %.3f",
                curMatrix.a[0][0], curMatrix.a[0][1], curMatrix.a[0][2],
                curMatrix.a[1][0], curMatrix.a[1][1], curMatrix.a[1][2],
                curMatrix.a[2][0], curMatrix.a[2][1], curMatrix.a[2][2]);
    auto box = this->boundingBox();
    ImGui::Text("\nItemBox: min(%.1f, %.1f) max(%.1f, %.1f)",
                bg::get<bg::min_corner, 0>(box), bg::get<bg::min_corner, 1>(box),
                bg::get<bg::max_corner, 0>(box), bg::get<bg::max_corner, 1>(box)
                );
    // clang-format on
    ImGui::End();
    ImGui::EndFrame();

    if (prevScale != scale) {
      this->setScale(scale.first, scale.second, this->anchor());
    }
    if (prevAngle != angle) {
      this->setRotation(angle, this->anchor());
    }
  };
}
