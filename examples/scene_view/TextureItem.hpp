// TextureItem.hpp

#pragma once

#include "BaseItem.hpp"
#include "KaliLaska/opengl.hpp"
#include <filesystem>

class TextureItem final : public BaseItem {
public:
  TextureItem(const std::filesystem::path &file);

  ItemType type() const override;

  void render(KaliLaska::GL::Renderer *renderer) const override;

  KaliLaska::Ring shape() const override;

  void mousePressEvent(KaliLaska::SceneMousePressEvent *event) override;
  void mouseReleaseEvent(KaliLaska::SceneMouseReleaseEvent *event) override;

private:
  KaliLaska::Ring              shape_;
  KaliLaska::GL::Texture       texture_;
  mutable KaliLaska::GL::Cache cache_;
};
