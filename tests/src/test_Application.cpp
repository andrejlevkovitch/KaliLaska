// test_Application.cpp

#define CATCH_CONFIG_RUNNER
#include "KaliLaska/Application.hpp"
#include <catch2/catch.hpp>
int main(int argc, char *argv[]) {
  KaliLaska::Application app{argc, argv};
  int                    result = Catch::Session().run(argc, argv);
  return result;
}

#include "KaliLaska/Window.hpp"

SCENARIO("Test Application", "[Application]") {
  GIVEN("Application") {
    WHEN("We get application") {
      THEN("Check Window creation") {
        std::unique_ptr<KaliLaska::Window> window;
        // we have to get window without exception
        REQUIRE_NOTHROW(window = std::make_unique<KaliLaska::Window>());
        CHECK(window);
      }
    }

    WHEN("We create one window") {
      KaliLaska::Window window;
      THEN("Process events for Application") {
        KaliLaska::Application::instance()->processEvents();

        WHEN("We close last window") {
          window.close();
          KaliLaska::Application::instance()->processEvents();

          // TODO
        }
      }
    }
  }
}
