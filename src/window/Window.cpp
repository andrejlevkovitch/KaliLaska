// Window.cpp

#include "KaliLaska/Window.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/CloseEvent.hpp"
#include "KaliLaska/imp/WindowImp.hpp"
#include "KaliLaska/imp/WindowImpFactory.hpp"
#include "debug.hpp"
#include <iostream>
#include <stdexcept>

#define WINDOW_CREATE_ERROR "Window can not be created"

namespace KaliLaska {
Window::Window()
    : imp_{nullptr} {
  if (auto factory = Application::windowFactory()) {
    imp_ = factory->createWindowImp(*this);
  }
  if (imp_ == nullptr) {
    throw std::runtime_error{WINDOW_CREATE_ERROR};
  }
}

Window::Window(const char *title, Size size)
    : imp_{nullptr} {
  if (auto factory = Application::windowFactory()) {
    imp_ = factory->createWindowImp(*this, title, size);
  }
  if (imp_ == nullptr) {
    throw std::runtime_error{WINDOW_CREATE_ERROR};
  }
}

Window::Window(const char *title, Point pos, Size size)
    : imp_{nullptr} {
  if (auto factory = Application::windowFactory()) {
    imp_ = factory->createWindowImp(*this, title, pos, size);
  }
  if (imp_ == nullptr) {
    throw std::runtime_error{WINDOW_CREATE_ERROR};
  }
}

Window::~Window() {
  // also if we manually remove window it have to unregisterd itself
  Application::windowFactory()->resetWindow(this);
}

Point Window::pos() const {
  return imp_->pos();
}

void Window::setPos(Point pos) {
  imp_->setPos(pos);
}

Size Window::size() const {
  return imp_->size();
}

Size Window::drawSize() const {
  return imp_->drawSize();
}

const char *Window::title() const {
  return imp_->title();
}

void Window::setTitle(const char *title) {
  imp_->setTitle(title);
}

bool Window::isHide() const {
  return imp_->isHide();
}

void Window::hide() {
  imp_->hide();
}

void Window::show() {
  imp_->show();
}

void Window::close() {
  this->closeEvent(std::make_unique<CloseEvent>());
}

void Window::closeEvent(std::unique_ptr<CloseEvent> event) {
  DEBUG_OUT(reinterpret_cast<const Event &>(*event.get()));
  UNUSED(event);
  // first we have to unregister window in factory
  Application::windowFactory()->resetWindow(this);
  // and after we destroy implementation
  imp_.reset();
}

void Window::mouseMoveEvent(std::unique_ptr<MouseMoveEvent> event) {
  DEBUG_OUT(reinterpret_cast<const Event &>(*event.get()));
  UNUSED(event);
}

void Window::mousePressEvent(std::unique_ptr<MousePressEvent> event) {
  DEBUG_OUT(reinterpret_cast<const Event &>(*event.get()));
  UNUSED(event);
}

void Window::mouseReleaseEvent(std::unique_ptr<MouseReleaseEvent> event) {
  DEBUG_OUT(reinterpret_cast<const Event &>(*event.get()));
  UNUSED(event);
}

void Window::mouseWheelEvent(std::unique_ptr<MouseWheelEvent> event) {
  DEBUG_OUT(reinterpret_cast<const Event &>(*event.get()));
  UNUSED(event);
}

void Window::mouseFocusEvent(std::unique_ptr<MouseFocusEvent> event) {
  DEBUG_OUT(reinterpret_cast<const Event &>(*event.get()));
  UNUSED(event);
}

void Window::showEvent(std::unique_ptr<ShowEvent> event) {
  DEBUG_OUT(reinterpret_cast<const Event &>(*event.get()));
  UNUSED(event);
}

void Window::resizeEvent(std::unique_ptr<ResizeEvent> event) {
  DEBUG_OUT(reinterpret_cast<const Event &>(*event.get()));
  UNUSED(event);
}
} // namespace KaliLaska
