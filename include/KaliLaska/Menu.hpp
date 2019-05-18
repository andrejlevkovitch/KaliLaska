// Menu.hpp

#pragma once

#include <functional>
#include <memory>
#include <string_view>

namespace KaliLaska {
class Window;
class MenuImp;

class Menu final {
public:
  /**\brief window window in which will be displayed the menu
   */
  Menu(Window &window);
  ~Menu();

  /**\return true if visible, otherwise - false. By default - false
   */
  bool isVisible() const;
  void setVisible(bool val);
  /**\return true if menu can be displaed, otherwise - false. By default - false
   */
  bool isValid() const;

  /**\brief the method set imgui menu
   */
  void setFunction(std::function<void(void)> function);

  void render() const;

private:
  std::unique_ptr<MenuImp> imp_;
};
} // namespace KaliLaska
