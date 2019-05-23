// ExampleScene.cpp

#include "ExampleScene.hpp"
#include "BaseItem.hpp"
#include "KaliLaska/AbstractGraphicsItem.hpp"
#include "KaliLaska/KeyPressEvent.hpp"
#include "KaliLaska/KeyReleaseEvent.hpp"
#include <iostream>

#define SCALE_FACTORS                                                          \
  { 1.1, 1.1 }
#define REVERS_FACTORS                                                         \
  { 1 / 1.1, 1 / 1.1 }

ExampleScene::ExampleScene()
    : turn_{Turn::None}
    , scale_{Scale::None} {
}

void ExampleScene::keyPressEvent(KaliLaska::KeyPressEvent *event) {
  switch (event->key()) {
  case KaliLaska::Keyboard::Key::Key_Left:
    turn_ = Turn::Left;
    break;
  case KaliLaska::Keyboard::Key::Key_Right:
    turn_ = Turn::Right;
    break;
  case KaliLaska::Keyboard::Key::Key_Up:
    scale_ = Scale::In;
    break;
  case KaliLaska::Keyboard::Key::Key_Down:
    scale_ = Scale::Out;
    break;

  case KaliLaska::Keyboard::Key::Key_R:
    if (auto grabbed = grabbedItem()) {
      removeItem(grabbed);
    }
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
  case KaliLaska::Keyboard::Key::Key_Up:
    if (scale_ == Scale::In) {
      scale_ = Scale::None;
    }
    break;
  case KaliLaska::Keyboard::Key::Key_Down:
    if (scale_ == Scale::Out) {
      scale_ = Scale::None;
    }
    break;
  default:
    break;
  }
}

void ExampleScene::update() {
  // TODO here we get all items at first, because rotation of item change scene
  std::list<KaliLaska::AbstractGraphicsItem *> items;
  std::copy(begin(), end(), std::back_inserter(items));
  switch (turn_) {
  case Turn::Left:
    for (auto i : items) {
      // if (i->type() == ExampleItem) {
      auto item = reinterpret_cast<BaseItem *>(i);
      item->rotate(KaliLaska::toRad(5));
      //}
    }
    break;
  case Turn::Right:
    for (auto i : items) {
      // if (i->type() == ExampleItem) {
      auto item = reinterpret_cast<BaseItem *>(i);
      item->rotate(KaliLaska::toRad(-5));
      //}
    }
    break;
  default:
    break;
  }

  switch (scale_) {
  case Scale::In:
    for (auto i : items) {
      if (i->type() ==
          static_cast<KaliLaska::AbstractGraphicsItem::ItemType>(RingItem)) {
        auto item = reinterpret_cast<BaseItem *>(i);
        item->scale(SCALE_FACTORS);
      }
    }
    break;
  case Scale::Out:
    for (auto i : items) {
      if (i->type() ==
          static_cast<KaliLaska::AbstractGraphicsItem::ItemType>(RingItem)) {
        auto item = reinterpret_cast<BaseItem *>(i);
        item->scale(REVERS_FACTORS);
      }
    }
    break;
  default:
    break;
  }
}
