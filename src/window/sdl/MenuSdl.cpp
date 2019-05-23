// MenuSdl.cpp

#include "MenuSdl.hpp"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "imgui_internal.h"

namespace KaliLaska {
MenuSdl::MenuSdl(SDL_Window *window)
    : window_{window} {
}

MenuSdl::~MenuSdl() {
}

void MenuSdl::setImgui(std::function<void(void)> imgui) {
  imgui_ = std::move(imgui);
}

void MenuSdl::render() const {
  if (imgui_) {
    ::ImGui_ImplOpenGL3_NewFrame();
    ::ImGui_ImplSDL2_NewFrame(window_);

    imgui_();

    ImGui::Render();
    ::ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
}
} // namespace KaliLaska
