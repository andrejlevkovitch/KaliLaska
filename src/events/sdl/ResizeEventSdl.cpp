// ResizeEventSdl.cpp

#include "ResizeEventSdl.hpp"
#include "debug.hpp"

namespace KaliLaska {
ResizeEventSdl::ResizeEventSdl(Size next)
    : event_{} {
  event_.data1 = next.width();
  event_.data2 = next.height();
}

ResizeEventSdl::ResizeEventSdl(SDL_WindowEvent event)
    : event_{event} {
}

Size ResizeEventSdl::currentSize() const {
  return Size{event_.data1, event_.data2};
}
} // namespace KaliLaska
