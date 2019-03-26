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
}

GraphicsScene::~GraphicsScene() {
}

GraphicsItem *GraphicsScene::itemAt(const Point &pos) const {
  return imp_->itemAt(pos);
}

std::list<GraphicsItem *> GraphicsScene::itemsAt(const Point &pos) const {
  return imp_->itemsAt(pos);
}

void GraphicsScene::addItem(std::shared_ptr<GraphicsItem> item) {
  imp_->addItem(std::move(item));
}

void GraphicsScene::removeItem(GraphicsItem *item) {
  imp_->removeItem(item);
}

GraphicsScene::ConstIterator GraphicsScene::begin() const {
  return ConstIterator{std::make_unique<SceneIterator>(imp_->begin())};
}

GraphicsScene::ConstIterator GraphicsScene::end() const {
  return ConstIterator{std::make_unique<SceneIterator>(imp_->end())};
}

void GraphicsScene::mouseMoveEvent(std::unique_ptr<SceneMouseMoveEvent> event) {
  // TODO not implement
  UNUSED(event);
}

void GraphicsScene::mousePressEvent(
    std::unique_ptr<SceneMousePressEvent> event) {
  // TODO not implement
  UNUSED(event);
}

void GraphicsScene::mouseReleaseEvent(
    std::unique_ptr<SceneMouseReleaseEvent> event) {
  // TODO not implement
  UNUSED(event);
}

void GraphicsScene::keyPressEvent(std::unique_ptr<KeyPressEvent> event) {
  // TODO not implement
  UNUSED(event);
}

void GraphicsScene::keyReleaseEvent(std::unique_ptr<KeyReleaseEvent> event) {
  // TODO not implement
  UNUSED(event);
}

void GraphicsScene::event(std::unique_ptr<Event> event) {
  // TODO not implement
  UNUSED(event);
}
} // namespace KaliLaska
