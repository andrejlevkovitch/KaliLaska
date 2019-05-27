// BaseItem.hpp

#pragma once

#include "KaliLaska/AbstractGraphicsItem.hpp"

class BaseItem : public KaliLaska::AbstractGraphicsItem {
public:
  BaseItem()
      : anchor_{0, 0} {}

  void setAnchor(const KaliLaska::PointF &anchor) { anchor_ = anchor; }
  KaliLaska::PointF anchor() const { return anchor_; }

  void rotate(float angle) {
    KaliLaska::AbstractGraphicsItem::rotate(angle, anchor_);
  }

  void scale(std::pair<float, float> factors) {
    KaliLaska::AbstractGraphicsItem::scale(factors, anchor_);
  }

  std::function<void(void)> contextMenu(const KaliLaska::Point &pos) {
    namespace bg = boost::geometry;

    return [this, clickPos = pos]() {
      ImGui::NewFrame();
      ImGui::Begin("ExampleItem",
                   nullptr,
                   ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_AlwaysAutoResize |
                       ImGuiWindowFlags_NoScrollbar);
      ImGui::SetWindowPos(::ImVec2(bg::get<0>(clickPos), bg::get<1>(clickPos)));

      auto  curMatrix = this->matrix();
      float angle     = this->getRotation();
      auto  scale = reinterpret_cast<AbstractGraphicsItem *>(this)->getScale();
      const auto prevScale = scale;
      const auto prevAngle = angle;

      ImGui::Text("%s", name_.c_str());
      ImGui::InputFloat2("item anchor", reinterpret_cast<float *>(&anchor_));
      ImGui::Separator();
      ImGui::SliderFloat2(
          "view scalse", reinterpret_cast<float *>(&scale), 0.1f, 10.f);
      ImGui::SliderAngle("view rotation", &angle);
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

  void setName(std::string_view name) { name_ = name; }

protected:
  KaliLaska::PointF anchor_;
  std::string       name_;
};
