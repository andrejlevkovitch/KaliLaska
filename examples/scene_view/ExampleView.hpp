// ExampleView.hpp

#pragma once

#include "KaliLaska/GraphicsView.hpp"
#include "KaliLaska/opengl.hpp"

class ExampleView : public KaliLaska::GraphicsView {
public:
  ExampleView(std::string_view        title,
              const KaliLaska::Point &pos,
              const KaliLaska::Size & size);

  void setScene(KaliLaska::GraphicsScene *scene) override;

  void update() override;

protected:
  void
  mouseWheelEvent(std::unique_ptr<KaliLaska::MouseWheelEvent> event) override;

  void keyPressEvent(std::unique_ptr<KaliLaska::KeyPressEvent> event) override;

private:
  std::chrono::time_point<std::chrono::system_clock> last_;
  std::unique_ptr<KaliLaska::GL::ShaderProgram>      prog_;
};
