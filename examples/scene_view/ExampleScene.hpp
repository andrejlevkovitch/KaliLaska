// ExampleScene.hpp

#pragma once

#include "KaliLaska/GraphicsScene.hpp"

class ExampleScene : public KaliLaska::GraphicsScene {
public:
  enum class Turn { None, Left, Right };
  ExampleScene();

  void keyPressEvent(KaliLaska::KeyPressEvent *event) override;
  void keyReleaseEvent(KaliLaska::KeyReleaseEvent *event) override;

  void update() override;

private:
  Turn turn_;
};
