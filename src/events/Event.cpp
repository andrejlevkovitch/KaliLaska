// Event.cpp

#include "KaliLaska/Event.hpp"
#include "KaliLaska/CloseEvent.hpp"
#include "KaliLaska/MouseMoveEvent.hpp"
#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/MouseReleaseEvent.hpp"
#include "KaliLaska/MouseWheelEvent.hpp"

namespace KaliLaska {
Event::Event(Type type)
    : type_{type} {
}

Event::Type Event::type() const {
  return type_;
}

std::ostream &operator<<(std::ostream &stream, const Event &event) {
  switch (event.type()) {
  case Event::Type::CloseEvent:
    stream << reinterpret_cast<const CloseEvent &>(event);
    break;
  case Event::Type::MouseMoveEvent:
    stream << reinterpret_cast<const MouseMoveEvent &>(event);
    break;
  case Event::Type::MousePressEvent:
    stream << reinterpret_cast<const MousePressEvent &>(event);
    break;
  case Event::Type::MouseReleaseEvent:
    stream << reinterpret_cast<const MouseReleaseEvent &>(event);
    break;
  case Event::Type::MouseWheelEvent:
    stream << reinterpret_cast<const MouseWheelEvent &>(event);
    break;
  default:
    stream << "unknow event type";
    break;
  }
  return stream;
}
} // namespace KaliLaska