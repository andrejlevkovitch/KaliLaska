// main.cpp

#include "KaliLaska/Application.hpp"
#include "Scene.hpp"
#include "TextureItem.hpp"
#include "View.hpp"
#include "shaders.hpp"

int main(int argc, char **argv) {
  KaliLaska::Application app{argc, argv};

  View view{"texture view", {0, 0}, {800, 800}};
  view.setProperty(KaliLaska::AbstractGraphicsView::Property::Movable);

  Scene scene{};
  view.setScene(&scene);

  auto texItem1 = std::make_shared<TextureItem>(png);
  texItem1->setScenePos({0, 0}, {0, 0});
  scene.addItem(std::move(texItem1));

  return app.exec();
}
