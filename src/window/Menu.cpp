// Menu.cpp

#include "KaliLaska/Menu.hpp"
#include "KaliLaska/Application.hpp"
#include "application/imp/ApplicationImp.hpp"
#include "window/imp/MenuImp.hpp"
#include "window/imp/WindowImpFactory.hpp"

namespace KaliLaska {
Menu::Menu(Window &window)
    : imp_{Application::implementation()->windowImpFactory()->createMenuImp(
          window)} {
}

Menu::~Menu() {
}

bool Menu::isVisible() const {
  return imp_->isVisible();
}

void Menu::setVisible(bool val) {
  imp_->setVisible(val);
}

bool Menu::isValid() const {
  return imp_->isValid();
}

void Menu::setFunction(std::function<void(void)> val) {
  imp_->setFunction(std::move(val));
}

void Menu::render() const {
  imp_->render();
}
} // namespace KaliLaska
