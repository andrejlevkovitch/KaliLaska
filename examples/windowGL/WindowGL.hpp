// WindowGL.hpp

#pragma once

#include "KaliLaska/Window.hpp"
#include "KaliLaska/opengl.hpp"

class WindowGL : public KaliLaska::Window {
public:
  WindowGL(std::string_view title, const KaliLaska::Size &size);

  ~WindowGL() override;

  void update() override;

private:
  std::chrono::time_point<std::chrono::system_clock> last_;

  KaliLaska::GL::Program shaderProgram_;
  KaliLaska::GL::Shader  vertexShader_;
  KaliLaska::GL::Shader  fragmentShader_;
};
