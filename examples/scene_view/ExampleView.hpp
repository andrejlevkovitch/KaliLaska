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
       mousePressEvent(std::unique_ptr<KaliLaska::MousePressEvent> event) override;
  void mouseReleaseEvent(
      std::unique_ptr<KaliLaska::MouseReleaseEvent> event) override;
  void
  mouseMoveEvent(std::unique_ptr<KaliLaska::MouseMoveEvent> event) override;
  void
  mouseFocusEvent(std::unique_ptr<KaliLaska::MouseFocusEvent> event) override;

private:
  std::chrono::time_point<std::chrono::system_clock> last_;
  KaliLaska::GL::ShaderProgram                       prog_;
  bool                                               moveState_;
};
