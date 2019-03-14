// MyWindow.hpp

#pragma once

#include "KaliLaska/Window.hpp"

class MyWindow : public KaliLaska::Window {
public:
  using Window::Window;

  void closeEvent(std::unique_ptr<KaliLaska::CloseEvent> event);
  void showEvent(std::unique_ptr<KaliLaska::ShowEvent> event);
  void resizeEvent(std::unique_ptr<KaliLaska::ResizeEvent> event);

  void mouseFocusEvent(std::unique_ptr<KaliLaska::MouseFocusEvent> event);
  void mouseMoveEvent(std::unique_ptr<KaliLaska::MouseMoveEvent> event);
  void mousePressEvent(std::unique_ptr<KaliLaska::MousePressEvent> event);
  void mouseReleaseEvent(std::unique_ptr<KaliLaska::MouseReleaseEvent> event);
};
