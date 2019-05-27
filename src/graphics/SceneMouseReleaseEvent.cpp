// SceneMouseReleaseEvent.cpp

#include "KaliLaska/SceneMouseReleaseEvent.hpp"
#include "KaliLaska/MouseReleaseEvent.hpp"
#include <boost/geometry.hpp>

namespace bg = boost::geometry;

namespace KaliLaska {
SceneMouseReleaseEvent::SceneMouseReleaseEvent(
    std::unique_ptr<MouseReleaseEvent> event, const TransformMatrix &matrix)
    : SceneEvent{Type::SceneMouseReleaseEvent}
    , event_{std::move(event)}
    , matrix_{matrix} {
}

SceneMouseReleaseEvent::~SceneMouseReleaseEvent() {
}

Mouse::Button SceneMouseReleaseEvent::button() const {
  return event_->button();
}

Mouse::Buttons SceneMouseReleaseEvent::buttons() const {
  return event_->buttons();
}

PointF SceneMouseReleaseEvent::clickPos() const {
  PointF rezultPos{0, 0};
  bg::transform(
      event_->clickPos(),
      rezultPos,
      bg::strategy::transform::matrix_transformer<float, 2, 2>(matrix_));
  return rezultPos;
}

Point SceneMouseReleaseEvent::clickViewPos() const {
  return event_->clickPos();
}

const TransformMatrix &SceneMouseReleaseEvent::matrix() const {
  return matrix_;
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &                           stream,
                         const KaliLaska::SceneMouseReleaseEvent &event) {
  using namespace KaliLaska;
  stream << "SceneMousePressEvent: clickPos " << event.clickPos()
         << ", viewClickPos " << event.clickViewPos() << ", button ";
  switch (event.button()) {
  case Mouse::Button::Left:
    stream << "Left";
    break;
  case Mouse::Button::Right:
    stream << "Right";
    break;
  case Mouse::Button::Middle:
    stream << "Middle";
    break;
  default:
    stream << "Unknow";
    break;
  }
  return stream;
  return stream;
}
