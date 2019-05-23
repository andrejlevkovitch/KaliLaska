// MyWindow.hpp

#pragma once

#include "KaliLaska/AbstractWindow.hpp"

class MyWindow : public KaliLaska::AbstractWindow {
public:
  using AbstractWindow::AbstractWindow;

  void update() override;
  void render() const override;

protected:
  void closeEvent(std::unique_ptr<KaliLaska::CloseEvent> event) override;
  void showEvent(std::unique_ptr<KaliLaska::ShowEvent> event) override;
  void resizeEvent(std::unique_ptr<KaliLaska::ResizeEvent> event) override;
  void moveEvent(std::unique_ptr<KaliLaska::MoveEvent> event) override;

  void
  mouseFocusEvent(std::unique_ptr<KaliLaska::MouseFocusEvent> event) override;
  void
  mouseMoveEvent(std::unique_ptr<KaliLaska::MouseMoveEvent> event) override;
  void
       mousePressEvent(std::unique_ptr<KaliLaska::MousePressEvent> event) override;
  void mouseReleaseEvent(
      std::unique_ptr<KaliLaska::MouseReleaseEvent> event) override;

  void keyboardFocusEvent(
      std::unique_ptr<KaliLaska::KeyboardFocusEvent> event) override;
  void keyPressEvent(std::unique_ptr<KaliLaska::KeyPressEvent> event) override;
  void
  keyReleaseEvent(std::unique_ptr<KaliLaska::KeyReleaseEvent> event) override;

  void userEvent(std::unique_ptr<KaliLaska::Event> event) override;
};
