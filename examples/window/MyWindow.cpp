// MyWindow.cpp

#include "MyWindow.hpp"
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
#include <iostream>

void MyWindow::closeEvent(std::unique_ptr<KaliLaska::CloseEvent> event) {
  std::cerr << *event << std::endl;
  KaliLaska::Window::closeEvent(std::move(event));
}

void MyWindow::showEvent(std::unique_ptr<KaliLaska::ShowEvent> event) {
  std::cerr << *event << std::endl;
}

void MyWindow::resizeEvent(std::unique_ptr<KaliLaska::ResizeEvent> event) {
  std::cerr << *event << std::endl;
}

void MyWindow::moveEvent(std::unique_ptr<KaliLaska::MoveEvent> event) {
  std::cerr << *event << std::endl;
}

void MyWindow::mouseFocusEvent(
    std::unique_ptr<KaliLaska::MouseFocusEvent> event) {
  std::cerr << *event << std::endl;
}

void MyWindow::mouseMoveEvent(
    std::unique_ptr<KaliLaska::MouseMoveEvent> event) {
  std::cerr << *event << std::endl;
}

void MyWindow::mousePressEvent(
    std::unique_ptr<KaliLaska::MousePressEvent> event) {
  std::cerr << *event << std::endl;
}

void MyWindow::mouseReleaseEvent(
    std::unique_ptr<KaliLaska::MouseReleaseEvent> event) {
  std::cerr << *event << std::endl;
}

void MyWindow::keyboardFocusEvent(
    std::unique_ptr<KaliLaska::KeyboardFocusEvent> event) {
  std::cerr << *event << std::endl;
}

void MyWindow::keyPressEvent(std::unique_ptr<KaliLaska::KeyPressEvent> event) {
  std::cerr << *event << std::endl;
}

void MyWindow::keyReleaseEvent(
    std::unique_ptr<KaliLaska::KeyReleaseEvent> event) {
  std::cerr << *event << std::endl;
}

void MyWindow::userEvent(std::unique_ptr<KaliLaska::Event> event) {
  (void)event;
  std::cerr << "USER EVENT" << std::endl;
}
