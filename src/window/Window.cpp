// Window.cpp

#include "KaliLaska/Window.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/CloseEvent.hpp"
#include "debug.hpp"
#include "imp/WindowImp.hpp"
#include "imp/WindowImpFactory.hpp"
#include <stdexcept>

#define INVALID_FACTORY                                                        \
  "Window factory is invalid. Maybe Application is not initialized?"

namespace KaliLaska {
Window::Window()
    : imp_{nullptr} {
  try {
    if (auto factory = Application::windowFactory()) {
      imp_ = factory->createWindowImp(*this);
    } else {
      throw std::runtime_error{INVALID_FACTORY};
    }
  } catch (std::runtime_error &) {
    throw;
  }
}

Window::Window(const char *title, Size size)
    : imp_{nullptr} {
  try {
    if (auto factory = Application::windowFactory()) {
      imp_ = factory->createWindowImp(*this, title, size);
    } else {
      throw std::runtime_error{INVALID_FACTORY};
    }
  } catch (std::runtime_error &) {
    throw;
  }
}

Window::Window(const char *title, Point pos, Size size)
    : imp_{nullptr} {
  try {
    if (auto factory = Application::windowFactory()) {
      imp_ = factory->createWindowImp(*this, title, pos, size);
    } else {
      throw std::runtime_error{INVALID_FACTORY};
    }
  } catch (std::runtime_error &) {
    throw;
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

void Window::setSize(Size size) {
  imp_->setSize(size);
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

void Window::setFullScr() {
  imp_->setFullScr();
}

bool Window::isFullScr() const {
  return imp_->isFullScr();
}

void Window::setResizable(bool value) {
  imp_->setResizable(value);
}

bool Window::isResizable() const {
  return imp_->isResizable();
}

void Window::close() {
  this->closeEvent(std::make_unique<CloseEvent>());
}

void Window::swapWindow() {
  imp_->swapWindow();
}

void Window::makeCurrent() {
  imp_->makeCurrent();
}

void Window::closeEvent(std::unique_ptr<CloseEvent> event) {
  UNUSED(event);
  // first we have to unregister window in factory
  Application::windowFactory()->resetWindow(this);
  // and after we destroy implementation
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

void Window::mouseFocusEvent(std::unique_ptr<MouseFocusEvent> event) {
  UNUSED(event);
}

void Window::showEvent(std::unique_ptr<ShowEvent> event) {
  UNUSED(event);
}

void Window::resizeEvent(std::unique_ptr<ResizeEvent> event) {
  UNUSED(event);
}

void Window::keyboardFocusEvent(std::unique_ptr<KeyboardFocusEvent> event) {
  UNUSED(event);
}

void Window::keyPressEvent(std::unique_ptr<KeyPressEvent> event) {
  UNUSED(event);
}

void Window::keyReleaseEvent(std::unique_ptr<KeyReleaseEvent> event) {
  UNUSED(event);
}

void Window::userEvent(std::unique_ptr<Event> event) {
  UNUSED(event);
}

void Window::moveEvent(std::unique_ptr<MoveEvent> event) {
  UNUSED(event);
}

void Window::update() {
}
} // namespace KaliLaska
