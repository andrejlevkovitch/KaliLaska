// ExampleScene.hpp

#pragma once

#include "KaliLaska/GraphicsItem.hpp"
#include "KaliLaska/GraphicsScene.hpp"

class ExampleScene : public KaliLaska::GraphicsScene {
public:
  enum class Turn { None, Left, Right };
  enum class Scale { None, In, Out };
  enum {
    ExampleItem = KaliLaska::GraphicsItem::UserType + 1,
    RingItem,
    TextureItem
  };
  ExampleScene();

  void keyPressEvent(KaliLaska::KeyPressEvent *event) override;
  void keyReleaseEvent(KaliLaska::KeyReleaseEvent *event) override;

  void update() override;

private:
  Turn  turn_;
  Scale scale_;
};
