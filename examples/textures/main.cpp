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
  texItem1->setName("full");

  auto texItem2 =
      std::make_unique<TextureItem>(png, KaliLaska::Box{{0, 0}, {400, 300}});
  texItem2->setScenePos({100, 100}, {0, 0});
  texItem2->setName("first");

  auto texItem3 = std::make_unique<TextureItem>(
      png, KaliLaska::Box{{400, 300}, {800, 600}});
  texItem3->setScenePos({500, 500}, {0, 0});
  texItem3->setName("second");

  auto texItem4 =
      std::make_unique<TextureItem>(png, KaliLaska::Box{{400, 0}, {800, 300}});
  texItem4->setScenePos({200, 100}, {0, 0});
  texItem4->setName("third");

  auto texItem5 =
      std::make_unique<TextureItem>(png, KaliLaska::Box{{0, 300}, {400, 600}});
  texItem5->setScenePos({200, 500}, {0, 0});
  texItem5->setName("four");

  scene.addItem(std::move(texItem1));
  scene.addItem(std::move(texItem2));
  scene.addItem(std::move(texItem3));
  scene.addItem(std::move(texItem4));
  scene.addItem(std::move(texItem5));

  return app.exec();
}
