// BaseItem.hpp

#pragma once

#include "KaliLaska/Color.hpp"
#include "KaliLaska/GraphicsItem.hpp"

class BaseItem : public KaliLaska::GraphicsItem {
public:
  BaseItem()
      : anchor_{0, 0}
      , color_{KaliLaska::Color::Colors::White} {}

  void setAnchor(const KaliLaska::PointF &anchor) { anchor_ = anchor; }
  KaliLaska::PointF anchor() const { return anchor_; }

  void rotate(float angle) { KaliLaska::GraphicsItem::rotate(angle, anchor_); }

  void scale(std::pair<float, float> factors) {
    KaliLaska::GraphicsItem::scale(factors, anchor_);
  }

  std::function<void(void)> contextMenu() {
    namespace bg = boost::geometry;

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
        this->setScale(scale, this->anchor());
      }
      if (prevAngle != angle) {
        this->setRotation(angle, this->anchor());
      }
    };
  }

protected:
  KaliLaska::PointF anchor_;
  KaliLaska::Color  color_;
};
