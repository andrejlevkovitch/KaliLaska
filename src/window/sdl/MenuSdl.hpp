// MenuSdl.hpp

#pragma once

#include "window/imp/MenuImp.hpp"

class SDL_Window;

namespace KaliLaska {
class MenuSdl final : public MenuImp {
public:
  MenuSdl(SDL_Window *window);
  ~MenuSdl() override;

  void setImgui(std::function<void(void)> function) override;
  void render() const override;
  bool isValid() const override;

private:
  SDL_Window *              window_;
  std::function<void(void)> imgui_;
};
} // namespace KaliLaska
