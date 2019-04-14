// ExampleView.hpp

#pragma once

#include "KaliLaska/GraphicsView.hpp"

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

  void resizeEvent(std::unique_ptr<KaliLaska::ResizeEvent> event) override;

private:
  std::chrono::time_point<std::chrono::system_clock> last_;
};
