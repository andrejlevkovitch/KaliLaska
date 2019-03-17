// TestWindow.hpp

#pragma once

#include "KaliLaska/CloseEvent.hpp"
#include "KaliLaska/KeyPressEvent.hpp"
#include "KaliLaska/KeyReleaseEvent.hpp"
#include "KaliLaska/KeyboardFocusEvent.hpp"
#include "KaliLaska/MouseFocusEvent.hpp"
#include "KaliLaska/MouseMoveEvent.hpp"
#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/MouseReleaseEvent.hpp"
#include "KaliLaska/MoveEvent.hpp"
#include "KaliLaska/ResizeEvent.hpp"
#include "KaliLaska/ShowEvent.hpp"
#include "KaliLaska/Window.hpp"

class TestWindow : public KaliLaska::Window {
public:
  using Window::Window;

  void closeEvent(std::unique_ptr<KaliLaska::CloseEvent> event) override {
    closeEvent_ = std::move(event);
  }
  void showEvent(std::unique_ptr<KaliLaska::ShowEvent> event) override {
    showEvent_ = std::move(event);
  }
  void resizeEvent(std::unique_ptr<KaliLaska::ResizeEvent> event) override {
    resizeEvent_ = std::move(event);
  }
  void moveEvent(std::unique_ptr<KaliLaska::MoveEvent> event) override {
    moveEvent_ = std::move(event);
  }

  void
  mouseFocusEvent(std::unique_ptr<KaliLaska::MouseFocusEvent> event) override {
    mouseFocusEvent_ = std::move(event);
  }
  void
  mouseMoveEvent(std::unique_ptr<KaliLaska::MouseMoveEvent> event) override {
    mouseMoveEvent_ = std::move(event);
  }
  void
  mousePressEvent(std::unique_ptr<KaliLaska::MousePressEvent> event) override {
    mousePressEvent_ = std::move(event);
  }
  void mouseReleaseEvent(
      std::unique_ptr<KaliLaska::MouseReleaseEvent> event) override {
    mouseReleaseEvent_ = std::move(event);
  }

  void keyboardFocusEvent(
      std::unique_ptr<KaliLaska::KeyboardFocusEvent> event) override {
    keyboardFocusEvent_ = std::move(event);
  }
  void keyPressEvent(std::unique_ptr<KaliLaska::KeyPressEvent> event) override {
    keyPressEvent_ = std::move(event);
  }
  void
  keyReleaseEvent(std::unique_ptr<KaliLaska::KeyReleaseEvent> event) override {
    keyReleaseEvent_ = std::move(event);
  }

  void userEvent(std::unique_ptr<KaliLaska::Event> event) override {
    userEvent_ = std::move(event);
  }

public:
  std::unique_ptr<KaliLaska::CloseEvent>         closeEvent_;
  std::unique_ptr<KaliLaska::ShowEvent>          showEvent_;
  std::unique_ptr<KaliLaska::ResizeEvent>        resizeEvent_;
  std::unique_ptr<KaliLaska::MoveEvent>          moveEvent_;
  std::unique_ptr<KaliLaska::KeyboardFocusEvent> keyboardFocusEvent_;
  std::unique_ptr<KaliLaska::KeyPressEvent>      keyPressEvent_;
  std::unique_ptr<KaliLaska::KeyReleaseEvent>    keyReleaseEvent_;
  std::unique_ptr<KaliLaska::MouseFocusEvent>    mouseFocusEvent_;
  std::unique_ptr<KaliLaska::MouseMoveEvent>     mouseMoveEvent_;
  std::unique_ptr<KaliLaska::MousePressEvent>    mousePressEvent_;
  std::unique_ptr<KaliLaska::MouseReleaseEvent>  mouseReleaseEvent_;
  std::unique_ptr<KaliLaska::Event>              userEvent_;
};
