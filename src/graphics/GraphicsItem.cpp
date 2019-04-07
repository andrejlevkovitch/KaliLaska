// GraphicsItem.cpp

#include "KaliLaska/GraphicsItem.hpp"
#include "KaliLaska/GraphicsScene.hpp"
#include "debug.hpp"
#include <algorithm>
#include <boost/geometry.hpp>
#include <boost/qvm/mat.hpp>
#include <boost/qvm/mat_operations.hpp>
#include <boost/qvm/mat_traits.hpp>

namespace bq = boost::qvm;
namespace bg = boost::geometry;

namespace KaliLaska {
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
  return getTranslation(matrix_);
}

void GraphicsItem::setPos(const PointF &pos) {
  // FIXME now it call setScenePos, I have ot change it later
  setScenePos(pos, {0, 0});
}

void GraphicsItem::setScenePos(const PointF &pos, const PointF &anchor) {
  // for get previous pos
  PointF                                                   prevPos;
  bg::strategy::transform::matrix_transformer<float, 2, 2> translate{matrix_};
  bg::transform(bg::return_centroid<PointF>(boundingBox()), prevPos, translate);

  bq::mat_traits<TransformMatrix>::write_element<0, 2>(matrix_) =
      bg::get<0>(pos) - bg::get<0>(anchor);
  bq::mat_traits<TransformMatrix>::write_element<1, 2>(matrix_) =
      bg::get<1>(pos) - bg::get<1>(anchor);

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

void GraphicsItem::rotate(float angle, const PointF &anchor) {
  // for get previous pos
  PointF                                                   prevPos;
  bg::strategy::transform::matrix_transformer<float, 2, 2> translate{matrix_};
  bg::transform(bg::return_centroid<PointF>(boundingBox()), prevPos, translate);

  // clang-format off
  TransformMatrix anchorMat{{
      {1, 0, bg::get<0>(anchor)},
      {0, 1, bg::get<1>(anchor)},
      {0, 0, 1}}};
  // clang-format on

  TransformMatrix rotationMat{};
  bq::set_rotz(rotationMat, toRad(angle));

  matrix_ *= anchorMat;
  matrix_ *= rotationMat;
  matrix_ *= bq::inverse(anchorMat);

  itemChanged(prevPos);
}

void GraphicsItem::setRotation(float angle, const PointF &anchor) {
  // for get previous pos
  PointF                                                   prevPos;
  bg::strategy::transform::matrix_transformer<float, 2, 2> translate{matrix_};
  bg::transform(bg::return_centroid<PointF>(boundingBox()), prevPos, translate);

  // clang-format off
  TransformMatrix anchorMat{{
        {1, 0, bg::get<0>(anchor)},
        {0, 1, bg::get<1>(anchor)},
        {0, 0, 1}}};
  // clang-format on

  // rotate back
  auto backRotationMat = bq::inverse(getRotaionMat(matrix_));

  // rotate to new value
  TransformMatrix rotationMat{};
  bq::set_rotz(rotationMat, toRad(angle));

  matrix_ *= backRotationMat;
  matrix_ *= anchorMat;
  matrix_ *= rotationMat;
  matrix_ *= bq::inverse(anchorMat);

  itemChanged(prevPos);
}

float GraphicsItem::angle() const {
  return toDegrees(getAngle(matrix_));
}

Box GraphicsItem::boundingBox() const {
  return bg::return_envelope<Box>(shape());
}

GraphicsItem::ItemType GraphicsItem::type() const {
  return ItemType::None;
}

void GraphicsItem::scale(float x, float y, const PointF &anchor) {
  PointF                                                   prevPos;
  bg::strategy::transform::matrix_transformer<float, 2, 2> translate{matrix_};
  bg::transform(bg::return_centroid<PointF>(boundingBox()), prevPos, translate);

  // clang-format off
  TransformMatrix scaleMat{{ {x, 0, 0},
                             {0, y, 0},
                             {0, 0, 1}}};

  TransformMatrix anchorMat{{{1, 0, bg::get<0>(anchor)},
                             {0, 1, bg::get<1>(anchor)},
                             {0, 0, 1}}};
  // clang-format on

  matrix_ *= anchorMat;
  matrix_ *= scaleMat;
  matrix_ *= bq::inverse(anchorMat);

  itemChanged(prevPos);
}

void GraphicsItem::setScale(float x, float y, const PointF &anchor) {
  // for get previous pos
  PointF                                                   prevPos;
  bg::strategy::transform::matrix_transformer<float, 2, 2> translate{matrix_};
  bg::transform(bg::return_centroid<PointF>(boundingBox()), prevPos, translate);

  // clang-format off
  TransformMatrix scaleMat{{ {x, 0, 0},
                             {0, y, 0},
                             {0, 0, 1}}};

  TransformMatrix anchorMat{{{1, 0, bg::get<0>(anchor)},
                             {0, 1, bg::get<1>(anchor)},
                             {0, 0, 1}}};
  // clang-format on

  // rotate back
  auto backScaleMat = bq::inverse(getScaleMat(matrix_));

  matrix_ *= backScaleMat;
  matrix_ *= anchorMat;
  matrix_ *= scaleMat;
  matrix_ *= bq::inverse(anchorMat);

  itemChanged(prevPos);
}

std::pair<float, float> GraphicsItem::scale() const {
  return getScale(matrix_);
}
} // namespace KaliLaska
