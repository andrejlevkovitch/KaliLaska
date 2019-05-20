// MoveEvent.cpp

#include "KaliLaska/MoveEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "application/imp/ApplicationImp.hpp"
#include "events/imp/EventImpFactory.hpp"
#include "events/imp/MoveEventImp.hpp"

namespace KaliLaska {
MoveEvent::MoveEvent(Point curPos)
    : Event{Type::MoveEvent}
    , imp_{Application::implementation()->eventImpFactory()->createMoveEventImp(
          curPos)} {
}

MoveEvent::MoveEvent(std::unique_ptr<MoveEventImp> imp)
    : Event{Type::MoveEvent}
    , imp_{std::move(imp)} {
}

MoveEvent::~MoveEvent() {
}

Point MoveEvent::currentPos() const {
  return imp_->currentPos();
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &              stream,
                         const KaliLaska::MoveEvent &event) {
  stream << "MoveEvent: curPos " << event.currentPos();
  return stream;
}
