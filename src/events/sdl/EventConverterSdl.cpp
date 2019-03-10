// EventConverterSdl.cpp

#include "EventConverterSdl.hpp"
#include "CloseEventSdl.hpp"
#include "KaliLaska/CloseEvent.hpp"
#include "KaliLaska/MouseMoveEvent.hpp"
#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/MouseReleaseEvent.hpp"
#include "KaliLaska/MouseWheelEvent.hpp"
#include "MouseMoveEventSdl.hpp"
#include "MousePressEventSdl.hpp"
#include "MouseReleaseEventSdl.hpp"
#include "MouseWheelEventSdl.hpp"
#include "window/sdl/WindowSdlFactory.hpp"

namespace KaliLaska {
std::pair<Window *, std::unique_ptr<Event>>
EventConverterSdl::convert(const SDL_Event &       event,
                           const WindowSdlFactory &factory) {
  switch (event.type) {
  case SDL_MOUSEMOTION:
    return convertMouseMoveEvent(event.motion, factory);
  case SDL_MOUSEBUTTONUP:
    return convertMouseReleaseEvent(event.button, factory);
  case SDL_MOUSEBUTTONDOWN:
    return convertMousePressEvent(event.button, factory);
  case SDL_MOUSEWHEEL:
    return convertMouseWheelEvent(event.wheel, factory);
    // TODO window event not only close
  case SDL_WINDOWEVENT:
    return convertWindowEvent(event.window, factory);
  default:
    return {nullptr, nullptr};
  }
}

std::pair<Window *, std::unique_ptr<Event>>
EventConverterSdl::convertMouseMoveEvent(const SDL_MouseMotionEvent &event,
                                         const WindowSdlFactory &    factory) {
  return {factory.getWindowFromId(event.windowID),
          std::make_unique<MouseMoveEvent>(
              std::make_unique<MouseMoveEventSdl>(event))};
}

std::pair<Window *, std::unique_ptr<Event>>
EventConverterSdl::convertMousePressEvent(const SDL_MouseButtonEvent &event,
                                          const WindowSdlFactory &    factory) {
  return {factory.getWindowFromId(event.windowID),
          std::make_unique<MousePressEvent>(
              std::make_unique<MousePressEventSdl>(event))};
}

std::pair<Window *, std::unique_ptr<Event>>
EventConverterSdl::convertMouseReleaseEvent(const SDL_MouseButtonEvent &event,
                                            const WindowSdlFactory &factory) {
  return {factory.getWindowFromId(event.windowID),
          std::make_unique<MouseReleaseEvent>(
              std::make_unique<MouseReleaseEventSdl>(event))};
}

std::pair<Window *, std::unique_ptr<Event>>
EventConverterSdl::convertMouseWheelEvent(const SDL_MouseWheelEvent &event,
                                          const WindowSdlFactory &   factory) {
  return {factory.getWindowFromId(event.windowID),
          std::make_unique<MouseWheelEvent>(
              std::make_unique<MouseWheelEventSdl>(event))};
}

std::pair<Window *, std::unique_ptr<Event>>
EventConverterSdl::convertWindowEvent(const SDL_WindowEvent & event,
                                      const WindowSdlFactory &factory) {
  switch (event.event) {
  case SDL_WINDOWEVENT_CLOSE:
    return convertCloseEvent(event, factory);
  default:
    return {nullptr, nullptr};
  }
}

std::pair<Window *, std::unique_ptr<Event>>
EventConverterSdl::convertCloseEvent(const SDL_WindowEvent & event,
                                     const WindowSdlFactory &factory) {
  return {factory.getWindowFromId(event.windowID),
          std::make_unique<CloseEvent>(std::make_unique<CloseEventSdl>(event))};
}
} // namespace KaliLaska
