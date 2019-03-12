# cmake for src

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

set(KaliLaska_SRC
  application/Application.cpp

  core/Point.cpp
  core/Size.cpp

  events/Event.cpp
  events/CloseEvent.cpp
  events/ShowEvent.cpp
  events/ResizeEvent.cpp
  events/MouseFocusEvent.cpp
  events/MouseMoveEvent.cpp
  events/MousePressEvent.cpp
  events/MouseReleaseEvent.cpp
  events/MouseWheelEvent.cpp
  events/EventNotifyer.cpp

  window/Window.cpp


  application/sdl/ApplicationSdl.cpp

  events/sdl/CloseEventSdl.cpp
  events/sdl/ShowEventSdl.cpp
  events/sdl/ResizeEventSdl.cpp
  events/sdl/MouseFocusEventSdl.cpp
  events/sdl/MouseMoveEventSdl.cpp
  events/sdl/MousePressEventSdl.cpp
  events/sdl/MouseReleaseEventSdl.cpp
  events/sdl/MouseWheelEventSdl.cpp
  events/sdl/SdlEvents.cpp
  events/sdl/EventConverterSdl.cpp
  events/sdl/EventSdlFactory.cpp

  window/sdl/WindowSdl.cpp
  window/sdl/WindowSdlFactory.cpp

  main.cpp
  )

add_executable(${PROJECT_NAME} ${KaliLaska_SRC})
target_compile_features(${PROJECT_NAME}
  PRIVATE
    cxx_std_17
  )
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    SDL2::SDL2
    ${OPENGL_gl_LIBRARY}
  )
target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
  )
