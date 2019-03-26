// GraphicsItem.cpp

#include "KaliLaska/GraphicsItem.hpp"
#include "debug.hpp"
#include <algorithm>

namespace KaliLaska {
GraphicsItem::GraphicsItem() {
}

GraphicsScene *GraphicsItem::scene() const {
  return scene_;
}

GraphicsItem *GraphicsItem::parent() const {
  return parent_;
}

void GraphicsItem::setParent(GraphicsItem *parent) {
  // We have to save previous postion in parent koordinates and set it after all
  // operations
  Point currentPos = pos();
  if (parent_) {
    parent_->removeFromChildren(this);
  }
  parent_ = parent;
  if (parent_) {
    parent_->addToChildren(this);
  }
  setPos(currentPos);
}

Point GraphicsItem::pos() const {
  // TODO implement
  return {};
}

Point GraphicsItem::scenePos() const {
  // TODO implement
  return {};
}

void GraphicsItem::setPos(const Point &pos) {
  // TODO implement
  UNUSED(pos);
}

void GraphicsItem::setScenePos(const Point &pos) {
  // TODO implement
  UNUSED(pos);
}

std::list<GraphicsItem *> GraphicsItem::children() const {
  std::list<GraphicsItem *> retval;
  std::copy(children_.begin(), children_.end(), std::back_inserter(retval));
  return retval;
}

void GraphicsItem::mouseMoveEvent(std::unique_ptr<SceneMouseMoveEvent> event) {
  // TODO implement
  UNUSED(event);
}

void GraphicsItem::mousePressEvent(
    std::unique_ptr<SceneMousePressEvent> event) {
  // TODO implement
  UNUSED(event);
}

void GraphicsItem::mouseReleaseEvent(
    std::unique_ptr<SceneMouseReleaseEvent> event) {
  // TODO implement
  UNUSED(event);
}

void GraphicsItem::userEvent(std::unique_ptr<Event> event) {
  // TODO implement
  UNUSED(event);
}

void GraphicsItem::addToChildren(GraphicsItem *item) {
  children_.insert(item);
}

void GraphicsItem::removeFromChildren(GraphicsItem *item) {
  if (auto found = children_.find(item); found != children_.end()) {
    children_.erase(found);
  }
}
} // namespace KaliLaska
