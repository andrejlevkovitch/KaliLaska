// Window.cpp

#include "KaliLaska/Window.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/WindowImp.hpp"
#include "KaliLaska/WindowImpFactory.hpp"
#include "debug.hpp"
#include <iostream>
#include <stdexcept>

// delete later
#include "KaliLaska/CloseEvent.hpp"
#include "KaliLaska/CloseEventImp.hpp"

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
  if (imp_ == nullptr || !imp_->isValid()) {
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
  UNUSED(event);
  imp_.reset();
}

void Window::mouseMoveEvent(std::unique_ptr<MouseMoveEvent> event) {
  UNUSED(event);
}

void Window::mousePressEvent(std::unique_ptr<MousePressEvent> event) {
  UNUSED(event);
}

void Window::mouseReleaseEvent(std::unique_ptr<MouseReleaseEvent> event) {
  UNUSED(event);
}

void Window::mouseWheelEvent(std::unique_ptr<MouseWheelEvent> event) {
  UNUSED(event);
}
} // namespace KaliLaska