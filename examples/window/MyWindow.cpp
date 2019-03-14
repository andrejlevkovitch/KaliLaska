// MyWindow.cpp

#include "MyWindow.hpp"
#include "KaliLaska/CloseEvent.hpp"
#include "KaliLaska/MouseFocusEvent.hpp"
#include "KaliLaska/MouseMoveEvent.hpp"
#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/MouseReleaseEvent.hpp"
#include "KaliLaska/ResizeEvent.hpp"
#include "KaliLaska/ShowEvent.hpp"
#include <iostream>

void MyWindow::closeEvent(std::unique_ptr<KaliLaska::CloseEvent> event) {
  std::cerr << *event << std::endl;
  KaliLaska::Window::closeEvent(std::move(event));
}

void MyWindow::showEvent(std::unique_ptr<KaliLaska::ShowEvent> event) {
  std::cerr << *event << std::endl;
  KaliLaska::Window::showEvent(std::move(event));
}

void MyWindow::resizeEvent(std::unique_ptr<KaliLaska::ResizeEvent> event) {
  std::cerr << *event << std::endl;
  KaliLaska::Window::resizeEvent(std::move(event));
}

void MyWindow::mouseFocusEvent(
    std::unique_ptr<KaliLaska::MouseFocusEvent> event) {
  std::cerr << *event << std::endl;
  KaliLaska::Window::mouseFocusEvent(std::move(event));
}

void MyWindow::mouseMoveEvent(
    std::unique_ptr<KaliLaska::MouseMoveEvent> event) {
  std::cerr << *event << std::endl;
  KaliLaska::Window::mouseMoveEvent(std::move(event));
}

void MyWindow::mousePressEvent(
    std::unique_ptr<KaliLaska::MousePressEvent> event) {
  std::cerr << *event << std::endl;
  KaliLaska::Window::mousePressEvent(std::move(event));
}

void MyWindow::mouseReleaseEvent(
    std::unique_ptr<KaliLaska::MouseReleaseEvent> event) {
  std::cerr << *event << std::endl;
  KaliLaska::Window::mouseReleaseEvent(std::move(event));
}
