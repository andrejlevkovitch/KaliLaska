// ExampleItem.hpp

#pragma once

#include "KaliLaska/Color.hpp"
#include "KaliLaska/GraphicsItem.hpp"

class ExampleItem final : public KaliLaska::GraphicsItem {
public:
  explicit ExampleItem(const KaliLaska::Color &color);

  KaliLaska::Ring shape() const override;
  void            render() const override;
  void            update() override;

  void mouseMoveEvent(KaliLaska::SceneMouseMoveEvent *event) override;
  void mousePressEvent(KaliLaska::SceneMousePressEvent *event) override;
  void mouseReleaseEvent(KaliLaska::SceneMouseReleaseEvent *event) override;

private:
  KaliLaska::Color color_;
};
