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
}

void GraphicsView::setProperty(Properties prop) {
  properties_ = prop;

  if (properties_ & Property::NotModificable) {
    state_ = UnModificableState::instance();
  }
}

GraphicsScene *GraphicsView::scene() const {
  return scene_;
}

void GraphicsView::setScene(GraphicsScene *scene) {
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
  Box                                                      retval;
  bg::strategy::transform::matrix_transformer<float, 2, 2> transform{matrix_};
  bg::transform(viewBox(), retval, transform);
  return retval;
}

Box GraphicsView::viewBox() const {
  return {{0, 0},
          {static_cast<float>(size().width()),
           static_cast<float>(size().height())}};
}

const TransformMatrix &GraphicsView::matrix() const {
  return matrix_;
}

TransformMatrix &GraphicsView::matrix() {
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
  state_ = state;
}
} // namespace KaliLaska
