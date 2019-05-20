// ResizeEvent.cpp

#include "KaliLaska/ResizeEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "application/imp/ApplicationImp.hpp"
#include "events/imp/EventImpFactory.hpp"
#include "events/imp/ResizeEventImp.hpp"

namespace KaliLaska {
ResizeEvent::ResizeEvent(Size newSize)
    : Event{Type::ResizeEvent}
    , imp_{Application::implementation()
               ->eventImpFactory()
               ->createResizeEventImp(newSize)} {
}

ResizeEvent::ResizeEvent(std::unique_ptr<ResizeEventImp> imp)
    : Event{Type::ResizeEvent}
    , imp_{std::move(imp)} {
}

ResizeEvent::~ResizeEvent() {
}

Size ResizeEvent::currentSize() const {
  return imp_->currentSize();
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &                stream,
                         const KaliLaska::ResizeEvent &event) {
  stream << "ResizeEvent: curSize " << event.currentSize();
  return stream;
}
