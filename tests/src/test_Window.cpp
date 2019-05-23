// test_Window.cpp

#define CATCH_CONFIG_RUNNER
#include "KaliLaska/Application.hpp"
#include <catch2/catch.hpp>
int main(int argc, char *argv[]) {
  KaliLaska::Application app{argc, argv};
  int                    result = Catch::Session().run(argc, argv);
  return result;
}

#include "KaliLaska/AbstractWindow.hpp"
#include "KaliLaska/Point.hpp"
#include "KaliLaska/Size.hpp"
#include <memory>

#define MY_TITLE "My Title"

class TestWindow final : public KaliLaska::AbstractWindow {
public:
  using AbstractWindow::AbstractWindow;
  void update() override{};
  void render() const override{};
};

SCENARIO("test window without parameters", "[Window]") {
  GIVEN("Window without parameters") {
    std::unique_ptr<KaliLaska::AbstractWindow> window;
    // we have to get window without exception
    REQUIRE_NOTHROW(window = std::make_unique<TestWindow>());

    WHEN("We get window") {
      REQUIRE(window != nullptr);

      THEN("Check caption") { CHECK(window->title() == std::string_view{""}); }
      AND_THEN("Check size") {
        // window size can not be null, but drawable size - can
        CHECK(window->size() != KaliLaska::Size{});
      }
      AND_THEN("Check status of window") {
        CHECK(window->isHide() == false);
        CHECK(window->isFullScr() == false);
        CHECK(window->isResizable() == false);
      }

      THEN("Check set options") {
        WHEN("We set caption of window") {
          window->setTitle(MY_TITLE);
          THEN("Check title") {
            CHECK(window->title() == std::string_view{MY_TITLE});
          }
        }
        AND_WHEN("We set size") {
          KaliLaska::Size newSize{100, 100};
          window->setSize(newSize);
          THEN("Check size") { CHECK(window->size() == newSize); }
        }
        AND_WHEN("We set pos") {
          KaliLaska::Point newPos{100, 100};
          window->setPos(newPos);
          THEN("Check pos") { CHECK(window->pos() == newPos); }
        }
        AND_WHEN("We change state of window") {
          WHEN("We change resizable state") {
            window->setResizable(true);
            THEN("Check resizable state") { CHECK(window->isResizable()); }
          }
          AND_WHEN("We set hide") {
            window->hide();
            THEN("Check hide") { CHECK(window->isHide()); }
            WHEN("Chenge back to show") {
              window->show();
              THEN("Check show") { CHECK_FALSE(window->isHide()); }
            }
          }
          AND_WHEN("We set to fullscr") {
            window->setFullScr();
            THEN("Check fullscr") { CHECK(window->isFullScr()); }
          }
        }
      }
    }
  }
}

SCENARIO("Test window with set size", "[Window]") {
  GIVEN("Window with set size") {
    std::unique_ptr<KaliLaska::AbstractWindow> window;
    KaliLaska::Size                            windowSize{200, 200};
    REQUIRE_NOTHROW(window =
                        std::make_unique<TestWindow>(MY_TITLE, windowSize));

    WHEN("We get window") {
      REQUIRE(window);
      THEN("Check caption") {
        CHECK(window->title() == std::string_view{MY_TITLE});
      }
      AND_THEN("Check size") { CHECK(window->size() == windowSize); }
    }
  }
}

SCENARIO("Test window with position and size", "[Window]") {
  GIVEN("Window with set size and pos") {
    std::unique_ptr<KaliLaska::AbstractWindow> window;
    KaliLaska::Size                            windowSize{200, 200};
    KaliLaska::Point                           windowPos{500, 259};
    REQUIRE_NOTHROW(
        window = std::make_unique<TestWindow>(MY_TITLE, windowPos, windowSize));

    WHEN("We get window") {
      REQUIRE(window);
      THEN("check caption") {
        CHECK(window->title() == std::string_view{MY_TITLE});
      }
      AND_THEN("Check size") { CHECK(window->size() == windowSize); }
      AND_THEN("Check pos") { CHECK(window->pos() == windowPos); }
    }
  }
}
