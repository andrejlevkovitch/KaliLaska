// test_GraphicsScene.cpp

#define CATCH_CONFIG_RUNNER
#include "KaliLaska/Application.hpp"
#include <catch2/catch.hpp>
int main(int argc, char *argv[]) {
  KaliLaska::Application app{argc, argv};
  int                    result = Catch::Session().run(argc, argv);
  return result;
}

#include "KaliLaska/GraphicsItem.hpp"
#include "KaliLaska/GraphicsScene.hpp"

class TestItem final : public KaliLaska::GraphicsItem {
public:
  void render() const override{};

  /**\brief all items have size{10, 10}
   */
  KaliLaska::Box boundingBox() const override { return {{0, 0}, {10, 10}}; };
};

SCENARIO("Test GraphicsScene", "[GraphicsScene]") {
  GIVEN("GraphicsScene instance") {
    KaliLaska::GraphicsScene scene;
    WHEN("We get scene") {
      THEN("Check it empty") {
        CHECK(scene.empty());
        CHECK(scene.size() == 0);
        CHECK(scene.begin() == scene.end());
      }
    }

    WHEN("Get items for test and set positions for this") {
      auto item0 = std::make_shared<TestItem>();
      auto item1 = std::make_shared<TestItem>();
      item1->setPos({250, 0});
      auto item2 = std::make_shared<TestItem>();
      item2->setPos({0, 150});
      auto item3 = std::make_shared<TestItem>();
      item3->setPos({600, 600});

      scene.addItem(item0);
      scene.addItem(item1);
      scene.addItem(item2);
      scene.addItem(item3);

      REQUIRE_FALSE(scene.empty());
      REQUIRE(scene.size() == 4);

      THEN("Check iterators") {
        REQUIRE(scene.begin() == scene.begin());
        REQUIRE(scene.end() == scene.end());
        REQUIRE(scene.end() != scene.begin());

        auto temp  = scene.begin();
        auto temp2 = temp;
        ++temp2;
        REQUIRE(temp2 != temp);
        REQUIRE(temp == scene.begin());
        REQUIRE(temp2 == ++scene.begin());

        auto iter = scene.begin();
        ++iter;
        ++iter;
        ++iter;
        ++iter;

        REQUIRE(iter == scene.end());

        auto found = std::find(scene.begin(), scene.end(), item3.get());
        REQUIRE(found != scene.end());
      }
      AND_THEN("Check size of scene by iterators") {
        auto count =
            std::count_if(scene.begin(), scene.end(), [](const auto &val) {
              (void)val;
              return true;
            });
        REQUIRE(count == scene.size());
      }

      THEN("Check itemAt method") {
        REQUIRE_FALSE(scene.itemAt({-1, -1}));

        REQUIRE(scene.itemAt({5, 5}) == item0.get());
        REQUIRE(scene.itemAt({253, 2}) == item1.get());
        REQUIRE(scene.itemAt({1, 151}) == item2.get());
        REQUIRE(scene.itemAt({609, 609}) == item3.get());

        REQUIRE(scene.itemAt({250, 0}) == item1.get());
        REQUIRE(scene.itemAt({610, 610}) == item3.get());
      }
      AND_THEN("Check itemsAt method") {
        auto list = scene.itemsAt({5, 5});
        REQUIRE_FALSE(list.empty());
        CHECK(list.size() == 1);

        list = scene.itemsAt(KaliLaska::Box{{0, 0}, {650, 650}});
        REQUIRE_FALSE(list.empty());
        CHECK(list.size() == 4);

        list = scene.itemsAt(KaliLaska::Box{{-1, -1}, {50, 160}});
        REQUIRE_FALSE(list.empty());
        CHECK(list.size() == 2);
      }

      THEN("Check remove") {
        WHEN("We remove by pointer") {
          scene.removeItem(item0.get());
          THEN("Check removing") {
            REQUIRE(scene.size() == 3);

            auto found = std::find(scene.begin(), scene.end(), item0.get());
            REQUIRE(found == scene.end());
          }
        }
        AND_WHEN("We remove by iterators") {
          auto ptr = *scene.begin();
          scene.removeItem(scene.begin());
          THEN("Check removing") {
            REQUIRE(scene.size() == 3);

            auto found = std::find(scene.begin(), scene.end(), ptr);
            REQUIRE(found == scene.end());
          }
        }
      }
      AND_THEN("Check clear method") {
        scene.clear();
        CHECK(scene.empty());
        CHECK(scene.size() == 0);
      }
    }
  }
}
