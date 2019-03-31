// GraphicsItem.cpp

#include "KaliLaska/GraphicsItem.hpp"
#include "debug.hpp"
#include <algorithm>
#include <boost/qvm/mat.hpp>
#include <boost/qvm/mat_traits.hpp>

namespace bq = boost::qvm;
namespace bg = boost::geometry;

namespace KaliLaska {
GraphicsItem::GraphicsItem()
    : matrix_{{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}} {
}

GraphicsScene *GraphicsItem::scene() const {
  return scene_;
}

GraphicsItem *GraphicsItem::parent() const {
  return parent_;
}

void GraphicsItem::setParent(GraphicsItem *parent) {
  // TODO change this
  // We have to save previous postion in parent koordinates and set it after all
  // operations
  PointF currentPos = pos();
  if (parent_) {
    parent_->removeFromChildren(this);
  }
  parent_ = parent;
  if (parent_) {
    parent_->addToChildren(this);
  }
  setPos(currentPos);
}

PointF GraphicsItem::pos() const {
  return {bq::mat_traits<TransformMatrix>::read_element<0, 2>(matrix_),
          bq::mat_traits<TransformMatrix>::read_element<1, 2>(matrix_)};
}

PointF GraphicsItem::scenePos() const {
  // TODO implement
  return {};
}

void GraphicsItem::setPos(const PointF &pos) {
  bq::mat_traits<TransformMatrix>::write_element<0, 2>(matrix_) =
      bg::get<0>(pos);
  bq::mat_traits<TransformMatrix>::write_element<1, 2>(matrix_) =
      bg::get<1>(pos);
}

void GraphicsItem::setScenePos(const PointF &pos) {
  // TODO implement
  UNUSED(pos);
}

std::list<GraphicsItem *> GraphicsItem::children() const {
  std::list<GraphicsItem *> retval;
  std::copy(children_.begin(), children_.end(), std::back_inserter(retval));
  return retval;
}

void GraphicsItem::mouseMoveEvent(SceneMouseMoveEvent *event) {
  // TODO implement
  UNUSED(event);
}

void GraphicsItem::mousePressEvent(SceneMousePressEvent *event) {
  // TODO implement
  UNUSED(event);
}

void GraphicsItem::mouseReleaseEvent(SceneMouseReleaseEvent *event) {
  // TODO implement
  UNUSED(event);
}

void GraphicsItem::userEvent(Event *event) {
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

const TransformMatrix &GraphicsItem::matrix() const {
  return matrix_;
}

TransformMatrix &GraphicsItem::matrix() {
  return matrix_;
}

void GraphicsItem::update() {
}
} // namespace KaliLaska
