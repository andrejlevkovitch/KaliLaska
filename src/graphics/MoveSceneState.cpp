// MoveSceneState.cpp

#include "MoveSceneState.hpp"
#include "KaliLaska/AbstractGraphicsView.hpp"
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
#include "debug.hpp"
#include <boost/geometry.hpp>

namespace bg = boost::geometry;
namespace bq = boost::qvm;

namespace KaliLaska {
static MoveSceneState instanceI;

ViewState *MoveSceneState::instance() {
  return &instanceI;
}

ViewState::Type MoveSceneState::type() const {
  return Type::MoveSceneState;
}

void MoveSceneState::mousePressEvent(
    AbstractGraphicsView *view, std::unique_ptr<MousePressEvent> event) const {
  UNUSED(view);
  UNUSED(event);
}

void MoveSceneState::mouseReleaseEvent(
    AbstractGraphicsView *             view,
    std::unique_ptr<MouseReleaseEvent> event) const {
  UNUSED(event);
  if (view->properties_ & AbstractGraphicsView::Property::NotModificable) {
    view->changeState(UnModificableState::instance());
  } else {
    view->changeState(NotifySceneState::instance());
  }
}

void MoveSceneState::mouseMoveEvent(
    AbstractGraphicsView *view, std::unique_ptr<MouseMoveEvent> event) const {
  if (view->scene_ && event) {
    bg::strategy::transform::matrix_transformer<float, 2, 2> transform{
        view->matrix_};

    PointF oldPos(-event->distance().x(), -event->distance().y());
    PointF newPos;
    bg::transform(oldPos, newPos, transform);

    bq::mat_traits<TransformMatrix>::write_element<0, 2>(view->matrix_) =
        bg::get<0>(newPos);
    bq::mat_traits<KaliLaska::TransformMatrix>::write_element<1, 2>(
        view->matrix_) = bg::get<1>(newPos);
  }
}

void MoveSceneState::keyPressEvent(AbstractGraphicsView *         view,
                                   std::unique_ptr<KeyPressEvent> event) const {
  UNUSED(view);
  UNUSED(event);
}

void MoveSceneState::keyReleaseEvent(
    AbstractGraphicsView *view, std::unique_ptr<KeyReleaseEvent> event) const {
  UNUSED(view);
  UNUSED(event);
}

void MoveSceneState::mouseFocusEvent(
    AbstractGraphicsView *view, std::unique_ptr<MouseFocusEvent> event) const {
  // we can get it only when lost focus, so just change state
  UNUSED(event);
  if (view->properties_ & AbstractGraphicsView::Property::NotModificable) {
    view->changeState(UnModificableState::instance());
  } else {
    view->changeState(NotifySceneState::instance());
  }
}
} // namespace KaliLaska
