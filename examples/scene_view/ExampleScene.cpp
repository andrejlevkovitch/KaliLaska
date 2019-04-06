// ExampleScene.cpp

#include "ExampleScene.hpp"
#include "KaliLaska/GraphicsItem.hpp"
#include "KaliLaska/KeyPressEvent.hpp"
#include "KaliLaska/KeyReleaseEvent.hpp"
#include <iostream>

ExampleScene::ExampleScene()
    : turn_{Turn::None} {
}

void ExampleScene::keyPressEvent(KaliLaska::KeyPressEvent *event) {
  switch (event->key()) {
  case KaliLaska::Keyboard::Key::Key_Left:
    turn_ = Turn::Left;
    break;
  case KaliLaska::Keyboard::Key::Key_Right:
    turn_ = Turn::Right;
    break;
  default:
    break;
  }
}

void ExampleScene::keyReleaseEvent(KaliLaska::KeyReleaseEvent *event) {
  switch (event->key()) {
  case KaliLaska::Keyboard::Key::Key_Left:
    if (turn_ == Turn::Left) {
      turn_ = Turn::None;
    }
    break;
  case KaliLaska::Keyboard::Key::Key_Right:
    if (turn_ == Turn::Right) {
      turn_ = Turn::None;
    }
    break;
  default:
    break;
  }
}

void ExampleScene::update() {
  // TODO here we get all items at first, because rotation of item change scene
  std::list<KaliLaska::GraphicsItem *> items;
  std::copy(begin(), end(), std::back_inserter(items));
  switch (turn_) {
  case Turn::Left:
    for (auto i : items) {
      i->rotate(5);
    }
    break;
  case Turn::Right:
    for (auto i : items) {
      i->rotate(-5);
    }
    break;
  default:
    break;
  }
}
