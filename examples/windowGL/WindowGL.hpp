// WindowGL.hpp

#pragma once

#include "KaliLaska/Window.hpp"

class WindowGL : public KaliLaska::Window {
public:
  WindowGL(std::string_view title, const KaliLaska::Size &size);

  ~WindowGL() override;

  void update() override;
  void render() const override;

private:
  std::chrono::time_point<std::chrono::system_clock> last_;
};
