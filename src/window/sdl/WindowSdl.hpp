// WindowSdl.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include "KaliLaska/Size.hpp"
#include "window/imp/WindowImp.hpp"

class SDL_Window;
struct ImGuiContext;

namespace KaliLaska {
class WindowSdlFactory;

class WindowSdl final : public WindowImp {
  friend WindowSdlFactory;

public:
  /**\throws when can not create window or OpenGL context
   */
  WindowSdl();
  WindowSdl(std::string_view title, Size size);
  WindowSdl(std::string_view title, Point pos, Size size);
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

  std::string_view title() const override;

  void setTitle(std::string_view title) override;

  bool isHide() const override;

  void hide() override;
  void show() override;

  void setFullScr() override;
  bool isFullScr() const override;

  void setResizable(bool value) override;
  bool isResizable() const override;

  void swapWindow() const override;

  void makeCurrent() const override;

protected:
  /**\return false when can not create window
   * \brief call in constructor
   */
  bool createWindow(const char *title, Point pos, Size size);
  /**\return false when can not create context
   * \brief call in constructor
   */
  bool createGLContext();

private:
  SDL_Window *  window_;
  void *        glContext_;
  ImGuiContext *imguiContext_;
};
} // namespace KaliLaska
