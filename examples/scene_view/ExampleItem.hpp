// ExampleItem.hpp

#pragma once

#include "KaliLaska/Color.hpp"
#include "KaliLaska/GraphicsItem.hpp"

class ExampleItem final : public KaliLaska::GraphicsItem {
public:
  explicit ExampleItem(const KaliLaska::Color &color);

  KaliLaska::Box boundingBox() const override;
  void           render() const override;
  void           update() override;

private:
  KaliLaska::Color color_;
};
