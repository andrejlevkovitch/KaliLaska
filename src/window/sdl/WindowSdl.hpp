// WindowSdl.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include "KaliLaska/Size.hpp"
#include "KaliLaska/imp/WindowImp.hpp"

class SDL_Window;

namespace KaliLaska {

class WindowSdl final : public WindowImp {
public:
  WindowSdl();
  WindowSdl(const char *title, Size size);
  WindowSdl(const char *title, Point pos, Size size);
  ~WindowSdl() override;

  WindowSdl(const WindowSdl &) = delete;
  WindowSdl &operator=(const WindowSdl &) = delete;

  /**\return SDL_Window id
   */
  uint32_t id() const;

  Point pos() const override;
  void  setPos(Point pos) override;

  Size size() const override;
  Size drawSize() const override;
  void setSize(Size size) override;

  const char *title() const override;

  void setTitle(const char *title) override;

  bool isValid() const override;

  bool isHide() const override;

  void hide() override;
  void show() override;
  void raise() override;

  void setFullScr() override;

  void minimize() override;
  void maximize() override;
  void restore() override;

private:
  SDL_Window *window_;
  bool        hidden_;
};
} // namespace KaliLaska
