// TextureItem.hpp

#pragma once

#include "BaseItem.hpp"
#include "KaliLaska/opengl.hpp"
#include <filesystem>
#include <string>

class TextureItem final : public BaseItem {
public:
  TextureItem(const std::filesystem::path &file);
  TextureItem(const std::filesystem::path &file,
              const KaliLaska::Box &       box,
              const KaliLaska::Ring &      textureShape = {
                  {0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}});

  void render(KaliLaska::GL::Renderer *renderer) const override;

  KaliLaska::Box boundingBox() const override;

  void mousePressEvent(KaliLaska::SceneMousePressEvent *event) override;
  void mouseReleaseEvent(KaliLaska::SceneMouseReleaseEvent *event) override;

private:
  KaliLaska::Box               box_;
  KaliLaska::GL::Texture       texture_;
  mutable KaliLaska::GL::Cache cache_;
};
