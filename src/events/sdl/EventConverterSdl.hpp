// EventConverterSdl.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include <SDL2/SDL.h>
#include <memory>

namespace KaliLaska {
class Window;
class WindowSdlFactory;

/**\brief create KaliLaska::Event-s from SDL events
 */
class EventConverterSdl final {
public:
  /**\param factory factory which create sdl windows. It also register
   * every window, and get interface, for get pointer to window, for which
   * the event
   */
  static std::pair<Window *, std::unique_ptr<Event>>
  convert(const SDL_Event &event, const WindowSdlFactory &factory);

private:
  static std::pair<Window *, std::unique_ptr<Event>>
  convertMouseMoveEvent(const SDL_MouseMotionEvent &event,
                        const WindowSdlFactory &    factory);

  static std::pair<Window *, std::unique_ptr<Event>>
  convertMousePressEvent(const SDL_MouseButtonEvent &event,
                         const WindowSdlFactory &    factory);

  static std::pair<Window *, std::unique_ptr<Event>>
  convertMouseReleaseEvent(const SDL_MouseButtonEvent &event,
                           const WindowSdlFactory &    factory);

  static std::pair<Window *, std::unique_ptr<Event>>
  convertMouseWheelEvent(const SDL_MouseWheelEvent &event,
                         const WindowSdlFactory &   factory);

  // window events--------------------------------------------------------------

  static std::pair<Window *, std::unique_ptr<Event>>
  convertWindowEvent(const SDL_WindowEvent & event,
                     const WindowSdlFactory &factory);

  static std::pair<Window *, std::unique_ptr<Event>>
  convertCloseEvent(const SDL_WindowEvent & event,
                    const WindowSdlFactory &factory);

  static std::pair<Window *, std::unique_ptr<Event>>
  convertShowEvent(const SDL_WindowEvent & event,
                   const WindowSdlFactory &factory);

  static std::pair<Window *, std::unique_ptr<Event>>
  convertMouseFocusEvent(const SDL_WindowEvent & event,
                         const WindowSdlFactory &factory);
};
} // namespace KaliLaska
