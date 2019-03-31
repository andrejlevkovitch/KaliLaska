// SceneMousePressEvent.cpp

#include "KaliLaska/SceneMousePressEvent.hpp"
#include "KaliLaska/MousePressEvent.hpp"
#include <boost/geometry.hpp>

namespace bg = boost::geometry;

namespace KaliLaska {
SceneMousePressEvent::SceneMousePressEvent(
    std::unique_ptr<MousePressEvent> event, const TransformMatrix &matrix)
    : SceneEvent{Type::SceneMousePressEvent}
    , event_{std::move(event)}
    , matrix_{matrix} {
}

SceneMousePressEvent::~SceneMousePressEvent() {
}

Mouse::Button SceneMousePressEvent::button() const {
  return event_->button();
}

Mouse::Buttons SceneMousePressEvent::buttons() const {
  return event_->buttons();
}

Mouse::Click SceneMousePressEvent::click() const {
  return event_->click();
}

PointF SceneMousePressEvent::clickPos() const {
  PointF rezultPos{0, 0};
  bg::transform(
      event_->clickPos(),
      rezultPos,
      bg::strategy::transform::matrix_transformer<float, 2, 2>(matrix_));
  return rezultPos;
}

Point SceneMousePressEvent::clickViewPos() const {
  return event_->clickPos();
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &                         stream,
                         const KaliLaska::SceneMousePressEvent &event) {
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
  stream << ", click " << static_cast<int>(event.click());
  return stream;
}
