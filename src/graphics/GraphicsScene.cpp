// GraphicsScene.cpp

#include "KaliLaska/GraphicsScene.hpp"
#include "IteratorImp.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/KeyPressEvent.hpp"
#include "KaliLaska/KeyReleaseEvent.hpp"
#include "KaliLaska/SceneMouseMoveEvent.hpp"
#include "KaliLaska/SceneMousePressEvent.hpp"
#include "KaliLaska/SceneMouseReleaseEvent.hpp"
#include "debug.hpp"
#include "imp/GraphicsSceneImpFactory.hpp"
#include "rtree/GraphicsSceneRTree.hpp"

namespace KaliLaska {
GraphicsScene::GraphicsScene()
    : imp_{Application::sceneFactory()->createGraphicsScene()} {
}

GraphicsScene::~GraphicsScene() {
}

GraphicsScene::ConstIterator GraphicsScene::begin() const {
  return ConstIterator{std::make_unique<IteratorImp>(imp_->begin())};
}

GraphicsScene::ConstIterator GraphicsScene::end() const {
  return ConstIterator{std::make_unique<IteratorImp>(imp_->end())};
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
