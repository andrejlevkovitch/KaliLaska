// GraphicsItem.cpp

#include "KaliLaska/GraphicsItem.hpp"
#include "KaliLaska/GraphicsScene.hpp"
#include "debug.hpp"
#include <algorithm>
#include <boost/qvm/mat.hpp>
#include <boost/qvm/mat_operations.hpp>
#include <boost/qvm/mat_traits.hpp>

namespace bq = boost::qvm;
namespace bg = boost::geometry;

namespace KaliLaska {
float toRad(float angle) {
  return angle * 3.14 / 180;
}

float toDegrees(float angle) {
  return angle * 180 / 3.14;
}

GraphicsItem::GraphicsItem()
    : scene_{}
    , parent_{}
    , matrix_{{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}} {
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
  // FIXME now it return rezult of scene pos, I have to change it later
  return scenePos();
}

PointF GraphicsItem::scenePos() const {
  return {bq::mat_traits<TransformMatrix>::read_element<0, 2>(matrix_),
          bq::mat_traits<TransformMatrix>::read_element<1, 2>(matrix_)};
}

void GraphicsItem::setPos(const PointF &pos) {
  // FIXME now it call setScenePos, I have ot change it later
  setScenePos(pos);
}

void GraphicsItem::setScenePos(const PointF &pos) {
  auto prevPos = scenePos();

  bq::mat_traits<TransformMatrix>::write_element<0, 2>(matrix_) =
      bg::get<0>(pos);
  bq::mat_traits<TransformMatrix>::write_element<1, 2>(matrix_) =
      bg::get<1>(pos);

  itemChanged(prevPos);
}

void GraphicsItem::itemChanged(const PointF &prevPos) const {
  if (scene_) {
    scene_->itemChanged(this, prevPos);
  }
}

std::list<GraphicsItem *> GraphicsItem::children() const {
  std::list<GraphicsItem *> retval;
  std::copy(children_.begin(), children_.end(), std::back_inserter(retval));
  return retval;
}

void GraphicsItem::mouseMoveEvent(SceneMouseMoveEvent *event) {
  UNUSED(event);
}

void GraphicsItem::mousePressEvent(SceneMousePressEvent *event) {
  UNUSED(event);
}

void GraphicsItem::mouseReleaseEvent(SceneMouseReleaseEvent *event) {
  UNUSED(event);
}

void GraphicsItem::userEvent(Event *event) {
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

void GraphicsItem::update() {
}

void GraphicsItem::rotate(float angle) {
  bq::rotate_z(matrix_, toRad(angle));
  itemChanged(pos());
}

void GraphicsItem::setRotation(float angle) {
  // TODO maybe is better way?
  float a        = bq::mat_traits<TransformMatrix>::read_element<0, 1>(matrix_);
  float b        = bq::mat_traits<TransformMatrix>::read_element<0, 0>(matrix_);
  float curAngle = std::atan2(-a, b);
  // rotate back
  bq::rotate_z(matrix_, -curAngle);
  // rotate to new value
  bq::rotate_z(matrix_, toRad(angle));
  itemChanged(pos());
}

float GraphicsItem::angle() const {
  float a = bq::mat_traits<TransformMatrix>::read_element<0, 1>(matrix_);
  float b = bq::mat_traits<TransformMatrix>::read_element<0, 0>(matrix_);
  return toDegrees(std::atan2(-a, b));
}
} // namespace KaliLaska
