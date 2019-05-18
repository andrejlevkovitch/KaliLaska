// MenuImgui.cpp

#include "MenuImgui.hpp"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "imgui_internal.h"

namespace KaliLaska {
MenuImgui::MenuImgui(SDL_Window *window)
    : window_{window}
    , visible_{false} {
}

MenuImgui::~MenuImgui() {
}

void MenuImgui::setVisible(bool val) {
  visible_ = val;
}

bool MenuImgui::isVisible() const {
  return visible_;
}

bool MenuImgui::isValid() const {
  return function_.operator bool();
}

void MenuImgui::setFunction(std::function<void(void)> function) {
  function_ = std::move(function);
}

void MenuImgui::render() const {
  if (visible_ && function_) {
    ::ImGui_ImplOpenGL3_NewFrame();
    ::ImGui_ImplSDL2_NewFrame(window_);

    function_();

    ImGui::Render();
    ::ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
}
} // namespace KaliLaska
