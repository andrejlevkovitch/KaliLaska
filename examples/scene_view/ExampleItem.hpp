// ExampleItem.hpp

#pragma once

#include "BaseItem.hpp"
#include "KaliLaska/Color.hpp"

class ExampleItem final : public BaseItem {
public:
  explicit ExampleItem(const KaliLaska::Color &color);

  ItemType type() const override;

  KaliLaska::Ring shape() const override;
  void            render(KaliLaska::GL::Renderer *renderer) const override;
  void            update() override;

  void mouseMoveEvent(KaliLaska::SceneMouseMoveEvent *event) override;
  void mousePressEvent(KaliLaska::SceneMousePressEvent *event) override;
  void mouseReleaseEvent(KaliLaska::SceneMouseReleaseEvent *event) override;

private:
  KaliLaska::Color color_;
};
