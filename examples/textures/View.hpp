// View.hpp

#pragma once

#include "KaliLaska/GraphicsView.hpp"

class View final : public KaliLaska::GraphicsView {
public:
  View(std::string_view        name,
       const KaliLaska::Point &pos,
       const KaliLaska::Size & size);

  void update() override;
  void render() const override;

private:
  std::chrono::time_point<std::chrono::system_clock> last_;

  KaliLaska::Color  clearColor_;
  KaliLaska::PointF anchor_;
};
