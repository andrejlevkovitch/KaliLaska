// ExampleScene.hpp

#pragma once

#include "KaliLaska/AbstractGraphicsItem.hpp"
#include "KaliLaska/GraphicsScene.hpp"

class ExampleScene : public KaliLaska::GraphicsScene {
public:
  enum class Turn { None, Left, Right };
  enum class Scale { None, In, Out };
  enum {
    ExampleItem = KaliLaska::AbstractGraphicsItem::UserType + 1,
    RingItem,
  };
  ExampleScene();

  void keyPressEvent(KaliLaska::KeyPressEvent *event) override;
  void keyReleaseEvent(KaliLaska::KeyReleaseEvent *event) override;

  void update() override;

private:
  Turn  turn_;
  Scale scale_;
};
