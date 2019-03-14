# cmake for src

include(GenerateExportHeader)

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
  )

add_library(${PROJECT_NAME} ${KaliLaska_SRC})
target_compile_features(${PROJECT_NAME}
  PRIVATE
    cxx_std_17
  )
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    SDL2::SDL2
    OpenGL::GL
  )
target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
  )
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/KaliLaska/kalilaska_export.h
  )
