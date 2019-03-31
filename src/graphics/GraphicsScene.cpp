// GraphicsScene.cpp

#include "KaliLaska/GraphicsScene.hpp"
#include "GraphicsSceneImpFactory.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/GraphicsItem.hpp"
#include "KaliLaska/KeyPressEvent.hpp"
#include "KaliLaska/KeyReleaseEvent.hpp"
#include "KaliLaska/SceneMouseMoveEvent.hpp"
#include "KaliLaska/SceneMousePressEvent.hpp"
#include "KaliLaska/SceneMouseReleaseEvent.hpp"
#include "debug.hpp"
#include "imp/GraphicsSceneImp.hpp"

namespace KaliLaska {
GraphicsScene::GraphicsScene()
    : imp_{GraphicsSceneImpFactory::createImp()} {
  Application::registerObject(this);
}

GraphicsScene::~GraphicsScene() {
  Application::unregisterObject(this);
}

GraphicsItem *GraphicsScene::itemAt(const PointF &pos, Spatials spat) const {
  return imp_->itemAt(pos, spat);
}

std::list<GraphicsItem *> GraphicsScene::itemsAt(const PointF &pos,
                                                 Spatials      spat) const {
  return imp_->itemsAt(pos, spat);
}

std::list<GraphicsItem *> GraphicsScene::itemsAt(const Box &box,
                                                 Spatials   spat) const {
  return imp_->itemsAt(box, spat);
}

void GraphicsScene::addItem(std::shared_ptr<GraphicsItem> item) {
  imp_->addItem(std::move(item));
}

void GraphicsScene::removeItem(GraphicsItem *item) {
  imp_->removeItem(item);
}

void GraphicsScene::removeItem(const ConstIterator &iter) {
  imp_->removeItem(*(iter.imp_));
}

GraphicsScene::ConstIterator GraphicsScene::begin() const {
  return ConstIterator{std::make_unique<SceneIterator>(imp_->begin())};
}

GraphicsScene::ConstIterator GraphicsScene::end() const {
  return ConstIterator{std::make_unique<SceneIterator>(imp_->end())};
}

size_t GraphicsScene::size() const {
  return imp_->size();
}

bool GraphicsScene::empty() const {
  return imp_->empty();
}

void GraphicsScene::clear() {
  return imp_->clear();
}

Box GraphicsScene::bounds() const {
  return imp_->bounds();
}

void GraphicsScene::mouseMoveEvent(SceneMouseMoveEvent *event) {
  if (event && !event->accepted()) {
    for (auto item : itemsAt(event->currentPos())) {
      item->mouseMoveEvent(event);
      if (event->accepted()) {
        break;
      }
    }
  }
}

void GraphicsScene::mousePressEvent(SceneMousePressEvent *event) {
  if (event && !event->accepted()) {
    for (auto item : itemsAt(event->clickPos())) {
      item->mousePressEvent(event);
      if (event->accepted()) {
        break;
      }
    }
  }
}

void GraphicsScene::mouseReleaseEvent(SceneMouseReleaseEvent *event) {
  if (event && !event->accepted()) {
    for (auto item : itemsAt(event->clickPos())) {
      item->mouseReleaseEvent(event);
      if (event->accepted()) {
        break;
      }
    }
  }
}

void GraphicsScene::mouseFocusEvent(MouseFocusEvent *event) {
  UNUSED(event);
}

void GraphicsScene::keyPressEvent(KeyPressEvent *event) {
  UNUSED(event);
}

void GraphicsScene::keyReleaseEvent(KeyReleaseEvent *event) {
  UNUSED(event);
}

void GraphicsScene::event(Event *event) {
  UNUSED(event);
}

void GraphicsScene::update() {
  for (auto i : *this) {
    i->update();
  }
}
} // namespace KaliLaska
