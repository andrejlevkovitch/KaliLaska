// MenuImp.hpp

#pragma once

#include <functional>
#include <string_view>

namespace KaliLaska {
class MenuImp {
public:
  virtual ~MenuImp() = default;

  /**\param val if true - menu is visible, if false - not
   */
  virtual void setVisible(bool val) = 0;
  /**\return true if menu is visible, otherwise - false
   */
  virtual bool isVisible() const = 0;

  /**\return true if menu can be displayed, otherwise - false
   */
  virtual bool isValid() const = 0;

  virtual void setFunction(std::function<void(void)> function) = 0;
  virtual void render() const                                  = 0;
};
} // namespace KaliLaska
