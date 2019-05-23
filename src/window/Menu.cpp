// Menu.cpp

#include "KaliLaska/Menu.hpp"
#include "KaliLaska/Application.hpp"
#include "application/imp/ApplicationImp.hpp"
#include "window/imp/MenuImp.hpp"
#include "window/imp/WindowImpFactory.hpp"

namespace KaliLaska {
Menu::Menu(AbstractWindow &window)
    : imp_{Application::implementation()->windowImpFactory()->createMenuImp(
          window)} {
}

Menu::~Menu() {
}

void Menu::setImgui(std::function<void(void)> imgui) {
  imp_->setImgui(std::move(imgui));
}

void Menu::render() const {
  imp_->render();
}
} // namespace KaliLaska
