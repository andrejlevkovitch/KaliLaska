// Event.cpp

#include "KaliLaska/Event.hpp"
#include "KaliLaska/CloseEvent.hpp"
#include "KaliLaska/KeyPressEvent.hpp"
#include "KaliLaska/KeyReleaseEvent.hpp"
#include "KaliLaska/KeyboardFocusEvent.hpp"
#include "KaliLaska/MouseFocusEvent.hpp"
#include "KaliLaska/MouseMoveEvent.hpp"
#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/MouseReleaseEvent.hpp"
#include "KaliLaska/MouseWheelEvent.hpp"
#include "KaliLaska/MoveEvent.hpp"
#include "KaliLaska/ResizeEvent.hpp"
#include "KaliLaska/ShowEvent.hpp"

namespace KaliLaska {
Event::Event(Type type)
    : type_{type} {
}

Event::Type Event::type() const {
  return type_;
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &stream, const KaliLaska::Event &event) {
  using namespace KaliLaska;
  switch (event.type()) {
  case Event::Type::CloseEvent:
    stream << reinterpret_cast<const CloseEvent &>(event);
    break;
  case Event::Type::ShowEvent:
    stream << reinterpret_cast<const ShowEvent &>(event);
    break;
  case Event::Type::ResizeEvent:
    stream << reinterpret_cast<const ResizeEvent &>(event);
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
  case Event::Type::MouseFocusEvent:
    stream << reinterpret_cast<const MouseFocusEvent &>(event);
    break;
  case Event::Type::KeyboardFocusEvent:
    stream << reinterpret_cast<const KeyboardFocusEvent &>(event);
    break;
  case Event::Type::KeyPressEvent:
    stream << reinterpret_cast<const KeyPressEvent &>(event);
    break;
  case Event::Type::KeyReleaseEvent:
    stream << reinterpret_cast<const KeyReleaseEvent &>(event);
    break;
  case Event::Type::MoveEvent:
    stream << reinterpret_cast<const MoveEvent &>(event);
    break;
  default:
    stream << "unknow event type";
    break;
  }
  return stream;
}
