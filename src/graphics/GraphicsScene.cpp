// GraphicsScene.cpp

#include "KaliLaska/GraphicsScene.hpp"
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
    // TODO not preaty, maybe use abstract factory?
    : imp_{Application::sceneFactory()->createGraphicsScene()} {
}

GraphicsScene::~GraphicsScene() {
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
