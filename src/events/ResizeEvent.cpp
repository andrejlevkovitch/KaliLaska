// ResizeEvent.cpp

#include "KaliLaska/ResizeEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/imp/EventImpFactory.hpp"

namespace KaliLaska {
ResizeEvent::ResizeEvent(Size newSize)
    : Event{Type::ResizeEvent}
    , imp_{Application::eventFactory()->createResizeEventImp(newSize)} {
}

ResizeEvent::ResizeEvent(std::unique_ptr<ResizeEventImp> imp)
    : Event{Type::ResizeEvent}
    , imp_{std::move(imp)} {
}

Size ResizeEvent::currentSize() const {
  return imp_->currentSize();
}

std::ostream &operator<<(std::ostream &stream, const ResizeEvent &event) {
  stream << "ResizeEvent: curSize " << event.currentSize();
  return stream;
}
} // namespace KaliLaska
