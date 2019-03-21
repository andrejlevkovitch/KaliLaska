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
    REQUIRE(KaliLaska::Application::instance());

    THEN("Check windowFactory") {
      CHECK(KaliLaska::Application::windowFactory());
    }

    THEN("Check eventFactory") {
      CHECK(KaliLaska::Application::eventFactory());
    }

    WHEN("We get application") {
      THEN("Check Window creation") {
        std::unique_ptr<KaliLaska::Window> window;
        // we have to get window without exception
        REQUIRE_NOTHROW(window = std::make_unique<KaliLaska::Window>());
        CHECK(window);
      }
    }

    WHEN("We set new time interval") {
      std::chrono::milliseconds newIterTime{682};
      KaliLaska::Application::instance()->setIterationTimeInterval(newIterTime);
      THEN("Check time interfal") {
        CHECK(KaliLaska::Application::instance()->iterationTimeInterval() ==
              newIterTime);
      }
    }
  }
}
