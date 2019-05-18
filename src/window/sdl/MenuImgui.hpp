// MenuImgui.hpp

#pragma once

#include "window/imp/MenuImp.hpp"

class SDL_Window;

namespace KaliLaska {
class MenuImgui final : public MenuImp {
public:
  MenuImgui(SDL_Window *window);
  ~MenuImgui() override;

  bool isVisible() const override;
  void setVisible(bool val) override;
  bool isValid() const override;

  void setFunction(std::function<void(void)> function) override;
  void render() const override;

private:
  SDL_Window *              window_;
  std::function<void(void)> function_;
  bool                      visible_;
};
} // namespace KaliLaska
