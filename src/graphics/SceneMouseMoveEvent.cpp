// SceneMouseMoveEvent.cpp

#include "KaliLaska/SceneMouseMoveEvent.hpp"
#include "KaliLaska/MouseMoveEvent.hpp"
#include <boost/geometry.hpp>

namespace bg = boost::geometry;
namespace bq = boost::qvm;

namespace KaliLaska {
SceneMouseMoveEvent::SceneMouseMoveEvent(std::unique_ptr<MouseMoveEvent> event,
                                         const TransformMatrix &         matrix)
    : SceneEvent{Event::Type::SceneMouseMoveEvent}
    , event_{std::move(event)}
    , matrix_{matrix} {
}

SceneMouseMoveEvent::~SceneMouseMoveEvent() {
}

Mouse::Buttons SceneMouseMoveEvent::buttons() const {
  return event_->buttons();
}

Point SceneMouseMoveEvent::currentViewPos() const {
  return event_->currentPos();
}

Point SceneMouseMoveEvent::previousViewPos() const {
  return event_->previousPos();
}

PointF SceneMouseMoveEvent::currentPos() const {
  PointF rezultPos{0, 0};
  bg::transform(
      event_->currentPos(),
      rezultPos,
      bg::strategy::transform::matrix_transformer<float, 2, 2>(matrix_));
  return rezultPos;
}

PointF SceneMouseMoveEvent::previousPos() const {
  PointF rezultPos{0, 0};
  bg::transform(
      event_->previousPos(),
      rezultPos,
      bg::strategy::transform::matrix_transformer<float, 2, 2>(matrix_));
  return rezultPos;
}

PointF SceneMouseMoveEvent::distance() const {
  PointF retval{0, 0};
  bg::transform(
      event_->distance(),
      retval,
      bg::strategy::transform::scale_transformer<float, 2, 2>(
          bq::mat_traits<TransformMatrix>::read_element<0, 0>(matrix_),
          bq::mat_traits<TransformMatrix>::read_element<1, 1>(matrix_)));
  return retval;
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &                        stream,
                         const KaliLaska::SceneMouseMoveEvent &event) {
  using namespace KaliLaska;
  stream << "SceneMouseMoveEvent: curPos " << event.currentPos() << ", prevPos "
         << event.previousPos() << ", curViewPos " << event.currentViewPos()
         << ", prevViewPos " << event.previousViewPos();
  if (auto buttons = event.buttons()) {
    stream << ", buttons";
    stream << ((buttons & Mouse::Button::Left) ? " Left" : "");
    stream << ((buttons & Mouse::Button::Right) ? " Right" : "");
    stream << ((buttons & Mouse::Button::Middle) ? " Middle" : "");
  }
  return stream;
}
