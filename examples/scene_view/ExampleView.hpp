// ExampleView.hpp

#pragma once

#include "KaliLaska/AbstractGraphicsView.hpp"
#include "KaliLaska/Menu.hpp"

class ExampleView : public KaliLaska::AbstractGraphicsView {
public:
  ExampleView(std::string_view        title,
              const KaliLaska::Point &pos,
              const KaliLaska::Size & size);
  ~ExampleView();

  void update() override;
  void render() const override;

protected:
  void
  mousePressEvent(std::unique_ptr<KaliLaska::MousePressEvent> event) override;

  void
  mouseWheelEvent(std::unique_ptr<KaliLaska::MouseWheelEvent> event) override;

  void keyPressEvent(std::unique_ptr<KaliLaska::KeyPressEvent> event) override;

  void resizeEvent(std::unique_ptr<KaliLaska::ResizeEvent> event) override;

private:
  std::chrono::time_point<std::chrono::system_clock> last_;
  std::unique_ptr<KaliLaska::Menu>                   menu_;

  KaliLaska::Color  clearColor_;
  KaliLaska::PointF anchor_;
};
