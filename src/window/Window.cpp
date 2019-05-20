// Window.cpp

#include "KaliLaska/Window.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/CloseEvent.hpp"
#include "KaliLaska/Menu.hpp"
#include "KaliLaska/opengl.hpp"
#include "application/imp/ApplicationImp.hpp"
#include "debug.hpp"
#include "logger/logger.hpp"
#include "window/imp/WindowImp.hpp"
#include "window/imp/WindowImpFactory.hpp"
#include <stdexcept>

#define INVALID_FACTORY                                                        \
  "Window factory is invalid. Maybe Application is not initialized?"

namespace KaliLaska {
Window::Window()
    : imp_{nullptr}
    , renderer_{std::make_unique<GL::Renderer>()} {
  LOG_TRACE << "Window: konstructor";
  try {
    if (auto factory = Application::implementation()->windowImpFactory()) {
      imp_ = factory->createWindowImp(*this);
    } else {
      LOG_THROW(std::runtime_error, INVALID_FACTORY);
    }
  } catch (std::runtime_error &) {
    throw;
  }
  Application::registerObject(this);
}

Window::Window(std::string_view title, const Size &size)
    : imp_{nullptr}
    , renderer_{std::make_unique<GL::Renderer>()} {
  LOG_TRACE << "Window: konstructor";
  try {
    if (auto factory = Application::implementation()->windowImpFactory()) {
      imp_ = factory->createWindowImp(*this, title, size);
    } else {
      LOG_THROW(std::runtime_error, INVALID_FACTORY);
    }
  } catch (std::runtime_error &) {
    throw;
  }
  Application::registerObject(this);
}

Window::Window(std::string_view title, const Point &pos, const Size &size)
    : imp_{nullptr}
    , renderer_{std::make_unique<GL::Renderer>()} {
  LOG_TRACE << "Window: konstructor";
  try {
    imp_ = Application::implementation()->windowImpFactory()->createWindowImp(
        *this, title, pos, size);
  } catch (std::runtime_error &) {
    throw;
  }
  Application::registerObject(this);
}

Window::~Window() {
  LOG_TRACE << "Window: destructor";
  // because it can be reset in close event
  // TODO I have two similar parts (here and in closeEvent)
  if (imp_) {
    renderer_.reset();
    // also if we manually remove window it have to unregisterd itself
    Application::unregisterObject(this);
  }
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

std::string_view Window::title() const {
  return imp_->title();
}

void Window::setTitle(std::string_view title) {
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

void Window::swapWindow() const {
  imp_->swapWindow();
}

void Window::makeCurrent() const {
  imp_->makeCurrent();
}

void Window::closeEvent(std::unique_ptr<CloseEvent> event) {
  LOG_TRACE << "Window close event " << this;
  UNUSED(event);
  // TODO I have two similar parts (here and in closeEvent)
  renderer_.reset();
  // also if we manually remove window it have to unregisterd itself
  Application::unregisterObject(this);
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
  // FIXME it call every time, it is not good
  std::remove_if(
      menus_.begin(), menus_.end(), [](const std::weak_ptr<Menu> &var) {
        if (!var.use_count()) {
          return true;
        }
        return false;
      });
}

GL::Renderer *Window::renderer() const {
  return renderer_.get();
}

void Window::setRenderer(std::unique_ptr<GL::Renderer> renderer) {
  renderer_ = std::move(renderer);
}

void Window::render() const {
  for (auto &i : menus_) {
    if (auto ptr = i.lock()) {
      ptr->render();
    }
  }
}

std::shared_ptr<Menu> Window::createMenu() {
  auto retval = std::make_shared<Menu>(*this);
  menus_.emplace_back(retval);
  return retval;
}
} // namespace KaliLaska
