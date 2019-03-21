// WindowSdl.cpp

#include "WindowSdl.hpp"
#include "KaliLaska/Color.hpp"
#include "KaliLaska/Point.hpp"
#include "KaliLaska/Size.hpp"
#include "debug.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace KaliLaska {
WindowSdl::WindowSdl()
    : WindowSdl{nullptr, {}, {}} {
}
WindowSdl::WindowSdl(const char *title, Size size)
    : WindowSdl{
          title, Point{SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED}, size} {
}

WindowSdl::WindowSdl(const char *title, Point pos, Size size)
    : window_{}
    , glContext_{} {
  if (!createWindow(title, pos, size) || !createGLContext()) {
    throw std::runtime_error{SDL_GetError()};
  }
}

WindowSdl::~WindowSdl() {
  SDL_GL_DeleteContext(glContext_);
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

bool WindowSdl::isHide() const {
  return SDL_GetWindowFlags(window_) & SDL_WINDOW_HIDDEN;
}

void WindowSdl::hide() {
  SDL_HideWindow(window_);
}

void WindowSdl::show() {
  SDL_ShowWindow(window_);
}

void WindowSdl::setFullScr() {
  ::SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

bool WindowSdl::isFullScr() const {
  return SDL_GetWindowFlags(window_) & SDL_WINDOW_FULLSCREEN_DESKTOP;
}

void WindowSdl::setResizable(bool value) {
  ::SDL_SetWindowResizable(window_, static_cast<SDL_bool>(value));
}

bool WindowSdl::isResizable() const {
  return ::SDL_GetWindowFlags(window_) & SDL_WINDOW_RESIZABLE;
}

void WindowSdl::swapWindow() {
  SDL_GL_SwapWindow(window_);
}

bool WindowSdl::createWindow(const char *title, Point pos, Size size) {
  window_ = SDL_CreateWindow(
      title, pos.x(), pos.y(), size.width(), size.height(), SDL_WINDOW_OPENGL);
  return window_;
}

bool WindowSdl::createGLContext() {
  glContext_ = SDL_GL_CreateContext(window_);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  swapWindow();
  return glContext_;
}

void WindowSdl::makeCurrent() {
  SDL_GL_MakeCurrent(window_, glContext_);
}
} // namespace KaliLaska
