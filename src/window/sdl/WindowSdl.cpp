// WindowSdl.cpp

#include "WindowSdl.hpp"
#include "KaliLaska/Point.hpp"
#include "KaliLaska/Size.hpp"
#include "debug.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
WindowSdl::WindowSdl()
    : window_{}
    , hidden_{false} {
  window_ = SDL_CreateWindow({}, 0, 0, 0, 0, SDL_WINDOW_OPENGL);
}
WindowSdl::WindowSdl(const char *title, Size size)
    : window_{}
    , hidden_{false} {
  window_ = SDL_CreateWindow(title,
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,
                             size.width(),
                             size.height(),
                             SDL_WINDOW_OPENGL);
}

WindowSdl::WindowSdl(const char *title, Point point, Size size)
    : window_{}
    , hidden_{false} {
  window_ = SDL_CreateWindow(title,
                             point.x(),
                             point.y(),
                             size.width(),
                             size.height(),
                             SDL_WINDOW_OPENGL);
}

WindowSdl::~WindowSdl() {
  SDL_DestroyWindow(window_);
}

uint32_t WindowSdl::id() const {
  return ::SDL_GetWindowID(window_);
}

Point WindowSdl::pos() const {
  int x{};
  int y{};
  SDL_GetWindowPosition(window_, &x, &y);
  return Point{x, y};
}

void WindowSdl::setPos(Point pos) {
  SDL_SetWindowPosition(window_, pos.x(), pos.y());
}

void WindowSdl::setSize(Size size) {
  SDL_SetWindowSize(window_, size.width(), size.height());
}

Size WindowSdl::size() const {
  int width{};
  int height{};
  SDL_GetWindowSize(window_, &width, &height);
  return Size{width, height};
}

Size WindowSdl::drawSize() const {
  int height{};
  int width{};
  SDL_GL_GetDrawableSize(window_, &width, &height);
  return Size{width, height};
}

const char *WindowSdl::title() const {
  return SDL_GetWindowTitle(window_);
}

void WindowSdl::setTitle(const char *title) {
  SDL_SetWindowTitle(window_, title);
}

bool WindowSdl::isValid() const {
  return window_;
}

bool WindowSdl::isHide() const {
  return hidden_;
}

void WindowSdl::hide() {
  SDL_HideWindow(window_);
  hidden_ = true;
}

void WindowSdl::show() {
  SDL_ShowWindow(window_);
  hidden_ = false;
}

void WindowSdl::minimize() {
  ::SDL_MinimizeWindow(window_);
}

void WindowSdl::maximize() {
  ::SDL_MaximizeWindow(window_);
}

void WindowSdl::restore() {
  ::SDL_RestoreWindow(window_);
}

void WindowSdl::raise() {
  ::SDL_RaiseWindow(window_);
}

void WindowSdl::setFullScr() {
  ::SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
}
} // namespace KaliLaska
