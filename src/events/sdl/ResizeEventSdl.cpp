// ResizeEventSdl.cpp

#include "ResizeEventSdl.hpp"
#include "debug.hpp"

namespace KaliLaska {
ResizeEventSdl::ResizeEventSdl(Size prev, Size next)
    : event_{} {
  // FIXME now we just ignore this value
  UNUSED(prev);
  event_.data1 = next.width();
  event_.data2 = next.height();
}

ResizeEventSdl::ResizeEventSdl(SDL_WindowEvent event)
    : event_{event} {
}

Size ResizeEventSdl::previousSize() const {
  // FIXME now here we just return invalid size
  return {};
}

Size ResizeEventSdl::newSize() const {
  return Size{event_.data1, event_.data2};
}
} // namespace KaliLaska
