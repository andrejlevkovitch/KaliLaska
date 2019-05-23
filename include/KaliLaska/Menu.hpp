// Menu.hpp

#pragma once

#include <functional>
#include <memory>
#include <string_view>

namespace KaliLaska {
class AbstractWindow;
class MenuImp;

/**\brief menu, based on imgui
 */
class Menu final {
public:
  /**\brief window window in which will be displayed the menu
   */
  Menu(AbstractWindow &window);
  ~Menu();

  /**\param imgui lyambda or functor in which describe some functionality by
   * imgui. Desribe what will be displayed. You need call all functions from
   * ImGui::NewFrame() to ImGui::EndFrame() inclusive (functions, which depends
   * from imgui implementations not needed, because it calls in Menu::render
   * before and after functionality which you set.
   */
  void setImgui(std::function<void(void)> imgui);

  void render() const;

private:
  std::unique_ptr<MenuImp> imp_;
};
} // namespace KaliLaska
