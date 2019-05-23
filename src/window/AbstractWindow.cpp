// AbstractWindow.cpp

#include "KaliLaska/AbstractWindow.hpp"
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
AbstractWindow::AbstractWindow()
    : imp_{nullptr}
    , renderer_{std::make_unique<GL::Renderer>()} {
  LOG_TRACE << "AbstractWindow: konstructor";
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

AbstractWindow::AbstractWindow(std::string_view title, const Size &size)
    : imp_{nullptr}
    , renderer_{std::make_unique<GL::Renderer>()} {
  LOG_TRACE << "AbstractWindow: konstructor";
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

AbstractWindow::AbstractWindow(std::string_view title,
                               const Point &    pos,
                               const Size &     size)
    : imp_{nullptr}
    , renderer_{std::make_unique<GL::Renderer>()} {
  LOG_TRACE << "AbstractWindow: konstructor";
  try {
    imp_ = Application::implementation()->windowImpFactory()->createWindowImp(
        *this, title, pos, size);
  } catch (std::runtime_error &) {
    throw;
  }
  Application::registerObject(this);
}

AbstractWindow::~AbstractWindow() {
  LOG_TRACE << "AbstractWindow: destructor";
  // because it can be reset in close event
  // TODO I have two similar parts (here and in closeEvent)
  if (imp_) {
    renderer_.reset();
    // also if we manually remove window it have to unregisterd itself
    Application::unregisterObject(this);
  }
}

Point AbstractWindow::pos() const {
  return imp_->pos();
}

void AbstractWindow::setPos(Point pos) {
  imp_->setPos(pos);
}

Size AbstractWindow::size() const {
  return imp_->size();
}

void AbstractWindow::setSize(Size size) {
  imp_->setSize(size);
}

Size AbstractWindow::drawSize() const {
  return imp_->drawSize();
}

std::string_view AbstractWindow::title() const {
  return imp_->title();
}

void AbstractWindow::setTitle(std::string_view title) {
  imp_->setTitle(title);
}

bool AbstractWindow::isHide() const {
  return imp_->isHide();
}

void AbstractWindow::hide() {
  imp_->hide();
}

void AbstractWindow::show() {
  imp_->show();
}

void AbstractWindow::setFullScr() {
  imp_->setFullScr();
}

bool AbstractWindow::isFullScr() const {
  return imp_->isFullScr();
}

void AbstractWindow::setResizable(bool value) {
  imp_->setResizable(value);
}

bool AbstractWindow::isResizable() const {
  return imp_->isResizable();
}

void AbstractWindow::close() {
  this->closeEvent(std::make_unique<CloseEvent>());
}

void AbstractWindow::swapWindow() const {
  imp_->swapWindow();
}

void AbstractWindow::makeCurrent() const {
  imp_->makeCurrent();
}

void AbstractWindow::closeEvent(std::unique_ptr<CloseEvent> event) {
  LOG_TRACE << "AbstractWindow close event " << this;
  UNUSED(event);
  // TODO I have two similar parts (here and in closeEvent)
  renderer_.reset();
  // also if we manually remove window it have to unregisterd itself
  Application::unregisterObject(this);
  imp_.reset();
}

void AbstractWindow::mouseMoveEvent(std::unique_ptr<MouseMoveEvent> event) {
  UNUSED(event);
}

void AbstractWindow::mousePressEvent(std::unique_ptr<MousePressEvent> event) {
  UNUSED(event);
}

void AbstractWindow::mouseReleaseEvent(
    std::unique_ptr<MouseReleaseEvent> event) {
  UNUSED(event);
}

void AbstractWindow::mouseWheelEvent(std::unique_ptr<MouseWheelEvent> event) {
  UNUSED(event);
}

void AbstractWindow::mouseFocusEvent(std::unique_ptr<MouseFocusEvent> event) {
  UNUSED(event);
}

void AbstractWindow::showEvent(std::unique_ptr<ShowEvent> event) {
  UNUSED(event);
}

void AbstractWindow::resizeEvent(std::unique_ptr<ResizeEvent> event) {
  UNUSED(event);
}

void AbstractWindow::keyboardFocusEvent(
    std::unique_ptr<KeyboardFocusEvent> event) {
  UNUSED(event);
}

void AbstractWindow::keyPressEvent(std::unique_ptr<KeyPressEvent> event) {
  UNUSED(event);
}

void AbstractWindow::keyReleaseEvent(std::unique_ptr<KeyReleaseEvent> event) {
  UNUSED(event);
}

void AbstractWindow::userEvent(std::unique_ptr<Event> event) {
  UNUSED(event);
}

void AbstractWindow::moveEvent(std::unique_ptr<MoveEvent> event) {
  UNUSED(event);
}

void AbstractWindow::update() {
}

GL::Renderer *AbstractWindow::renderer() const {
  return renderer_.get();
}

void AbstractWindow::setRenderer(std::unique_ptr<GL::Renderer> renderer) {
  renderer_ = std::move(renderer);
}

void AbstractWindow::render() const {
}
} // namespace KaliLaska
