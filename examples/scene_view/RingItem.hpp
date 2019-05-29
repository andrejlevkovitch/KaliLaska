// RingItem.hpp

#pragma once

#include "BaseItem.hpp"
#include "KaliLaska/Ring.hpp"
#include "KaliLaska/opengl.hpp"

class RingItem final : public BaseItem {
public:
  RingItem();

  ItemType type() const override;

  void update() override;
  void render(KaliLaska::GL::Renderer *renderer) const override;

  KaliLaska::Ring shape() const;

  KaliLaska::Box boundingBox() const override;

  void mousePressEvent(KaliLaska::SceneMousePressEvent *event) override;
  void mouseReleaseEvent(KaliLaska::SceneMouseReleaseEvent *event) override;

private:
  KaliLaska::Ring              shape_;
  mutable KaliLaska::GL::Cache cache_;
};
