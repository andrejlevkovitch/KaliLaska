// GraphicsView.cpp

#include "KaliLaska/GraphicsView.hpp"
#include "KaliLaska/GraphicsItem.hpp"
#include "KaliLaska/GraphicsScene.hpp"
#include "KaliLaska/KeyPressEvent.hpp"
#include "KaliLaska/KeyReleaseEvent.hpp"
#include "KaliLaska/MouseFocusEvent.hpp"
#include "KaliLaska/MouseMoveEvent.hpp"
#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/MouseReleaseEvent.hpp"
#include "KaliLaska/SceneMouseMoveEvent.hpp"
#include "KaliLaska/SceneMousePressEvent.hpp"
#include "KaliLaska/SceneMouseReleaseEvent.hpp"
#include "NotifySceneState.hpp"
#include "UnModificableState.hpp"
#include "ViewState.hpp"
#include "debug.hpp"
#include "logger/logger.hpp"
#include <boost/geometry.hpp>

namespace bg = boost::geometry;
namespace bq = boost::qvm;

namespace KaliLaska {
GraphicsView::GraphicsView(std::string_view title,
                           const Point &    pos,
                           const Size &     size)
    : Window{title, pos, size}
    , scene_{}
    , matrix_{{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}
    , state_{NotifySceneState::instance()}
    , properties_{} {
  LOG_TRACE << "GraphicsView: konstructor";
}

void GraphicsView::setProperty(Properties prop) {
  LOG_DEBUG << "GraphicsView: set property " << std::to_string(prop);
  properties_ = prop;

  if (properties_ & Property::NotModificable) {
    state_ = UnModificableState::instance();
  }
}

GraphicsScene *GraphicsView::scene() const {
  return scene_;
}

void GraphicsView::setScene(GraphicsScene *scene) {
  LOG_DEBUG << "GraphicsView: set scene " << scene;
  scene_ = scene;
}

void GraphicsView::update() {
}

void GraphicsView::setSceneBox(const Box &sceneBox) {
  bq::mat_traits<TransformMatrix>::write_element<0, 2>(matrix_) =
      bg::get<0>(sceneBox.min_corner());
  bq::mat_traits<TransformMatrix>::write_element<1, 2>(matrix_) =
      bg::get<1>(sceneBox.min_corner());

  auto sizeSceneBox = sceneBox.max_corner();
  bg::subtract_point(sizeSceneBox, sceneBox.min_corner());
  auto sizeViewBox = viewBox().max_corner();
  bg::subtract_point(sizeViewBox, viewBox().min_corner());

  bg::divide_point(sizeSceneBox, sizeViewBox);

  bq::mat_traits<TransformMatrix>::write_element<0, 0>(matrix_) =
      bg::get<0>(sizeSceneBox);
  bq::mat_traits<TransformMatrix>::write_element<1, 1>(matrix_) =
      bg::get<1>(sizeSceneBox);
}

Box GraphicsView::sceneBox() const {
  Ring view;
  bg::convert(viewBox(), view);
  Ring                                                     sceneRing;
  bg::strategy::transform::matrix_transformer<float, 2, 2> transform{matrix_};
  bg::transform(view, sceneRing, transform);
  return bg::return_envelope<Box>(sceneRing);
}

Box GraphicsView::viewBox() const {
  return {{0, 0},
          {static_cast<float>(drawSize().width()),
           static_cast<float>(drawSize().height())}};
}

const TransformMatrix &GraphicsView::matrix() const {
  return matrix_;
}

TransformMatrix &GraphicsView::matrixC() {
  return matrix_;
}

void GraphicsView::mousePressEvent(std::unique_ptr<MousePressEvent> event) {
  state_->mousePressEvent(this, std::move(event));
}

void GraphicsView::mouseReleaseEvent(std::unique_ptr<MouseReleaseEvent> event) {
  state_->mouseReleaseEvent(this, std::move(event));
}

void GraphicsView::mouseMoveEvent(std::unique_ptr<MouseMoveEvent> event) {
  state_->mouseMoveEvent(this, std::move(event));
}

void GraphicsView::keyPressEvent(std::unique_ptr<KeyPressEvent> event) {
  state_->keyPressEvent(this, std::move(event));
}

void GraphicsView::keyReleaseEvent(std::unique_ptr<KeyReleaseEvent> event) {
  state_->keyReleaseEvent(this, std::move(event));
}

void GraphicsView::mouseFocusEvent(std::unique_ptr<MouseFocusEvent> event) {
  state_->mouseFocusEvent(this, std::move(event));
}

void GraphicsView::changeState(ViewState *state) {
  LOG_DEBUG << "GraphicsView: state changed to " << state->type();
  state_ = state;
}

void GraphicsView::scale(float x, float y, const PointF &anchor) {
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
}

void GraphicsView::setScale(float         xFactor,
                            float         yFactor,
                            const PointF &anchor) {
  // clang-format off
  TransformMatrix scaleMat{{ {xFactor, 0, 0},
                             {0, yFactor, 0},
                             {0, 0, 1}}};

  TransformMatrix anchorMat{{{1, 0, bg::get<0>(anchor)},
                             {0, 1, bg::get<1>(anchor)},
                             {0, 0, 1}}};
  // clang-format on

  auto backScaleMat = bq::inverse(getScaleMat(matrix_));

  matrix_ *= anchorMat;
  matrix_ *= backScaleMat;
  matrix_ *= scaleMat;
  matrix_ *= bq::inverse(anchorMat);
}

std::pair<float, float> GraphicsView::scale() const {
  return getScale(matrix_);
}

void GraphicsView::rotate(float angle, const PointF &anchor) {
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
}

void GraphicsView::setRotation(float angle, const PointF &anchor) {
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

  matrix_ *= anchorMat;
  matrix_ *= backRotationMat;
  matrix_ *= rotationMat;
  matrix_ *= bq::inverse(anchorMat);
}

float GraphicsView::angle() const {
  return getAngle(matrix_);
}
} // namespace KaliLaska
