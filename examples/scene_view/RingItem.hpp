// RingItem.hpp

#pragma once

#include "BaseItem.hpp"
#include "KaliLaska/Ring.hpp"

class RingItem final : public BaseItem {
public:
  RingItem();

  ItemType type() const override;

  void update() override;
  void render() const override;

  KaliLaska::Ring shape() const override;

  void mousePressEvent(KaliLaska::SceneMousePressEvent *event) override;
  void mouseReleaseEvent(KaliLaska::SceneMouseReleaseEvent *event) override;

private:
  KaliLaska::Ring shape_;
};
