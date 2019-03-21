// WindowGL.hpp

#pragma once

#include "KaliLaska/Window.hpp"

class WindowGL : public KaliLaska::Window {
public:
  WindowGL(const char *title, KaliLaska::Size size);

  ~WindowGL() override;

  void update() override;

private:
  std::chrono::time_point<std::chrono::system_clock> last_;

  uint32_t shaderProgram_;
  uint32_t vertexShader_;
  uint32_t fragmentShader_;
};
