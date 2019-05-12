# cmake for src

find_package(Boost COMPONENTS log REQUIRED)

include(GenerateExportHeader)

set(geometry_SRC
  geometry/Point.cpp
  geometry/Size.cpp
  geometry/Color.cpp
  geometry/Box.cpp
  geometry/Ring.cpp
  geometry/TransformMatrix.cpp
  )

set(application_SRC
  application/EventNotifyer.cpp
  application/Application.cpp
  application/AppFactory.cpp

  application/sdl/ApplicationSdl.cpp
  )

set(events_SRC
  events/EventFactory.cpp

  events/Event.cpp
  events/CloseEvent.cpp
  events/ShowEvent.cpp
  events/ResizeEvent.cpp
  events/MoveEvent.cpp
  events/MouseFocusEvent.cpp
  events/MouseMoveEvent.cpp
  events/MousePressEvent.cpp
  events/MouseReleaseEvent.cpp
  events/MouseWheelEvent.cpp
  events/KeyboardFocusEvent.cpp
  events/KeyPressEvent.cpp
  events/KeyReleaseEvent.cpp
  events/KeyPrinter.cpp


  events/sdl/EventConverterSdl.cpp
  events/sdl/EventSdlFactory.cpp
  events/sdl/SdlEvents.cpp

  events/sdl/CloseEventSdl.cpp
  events/sdl/ShowEventSdl.cpp
  events/sdl/ResizeEventSdl.cpp
  events/sdl/MoveEventSdl.cpp
  events/sdl/MouseFocusEventSdl.cpp
  events/sdl/MouseMoveEventSdl.cpp
  events/sdl/MousePressEventSdl.cpp
  events/sdl/MouseReleaseEventSdl.cpp
  events/sdl/MouseWheelEventSdl.cpp
  events/sdl/KeyboardFocusEventSdl.cpp
  events/sdl/KeyPressEventSdl.cpp
  events/sdl/KeyReleaseEventSdl.cpp
  )

set(window_SRC
  window/Window.cpp

  window/sdl/WindowSdl.cpp
  window/sdl/WindowSdlFactory.cpp
  )

set(graphics_SRC
  graphics/GraphicsItem.cpp
  graphics/GraphicsScene.cpp
  graphics/ConstIterator.cpp
  graphics/GraphicsView.cpp
  graphics/SceneMouseMoveEvent.cpp
  graphics/SceneMousePressEvent.cpp
  graphics/SceneMouseReleaseEvent.cpp
  graphics/GraphicsSceneImpFactory.cpp

  graphics/MoveSceneState.cpp
  graphics/NotifySceneState.cpp
  graphics/UnModificableState.cpp

  graphics/imp/SceneIterator.cpp

  graphics/rtree/GraphicsSceneRTree.cpp
  graphics/rtree/SceneIteratorRTree.cpp
  )


set(KaliLaska_SRC
  logger/logger.cpp

  opengl/Program.cpp
  opengl/Renderer.cpp
  opengl/Cache.cpp

  opengl/Picture.cpp
  opengl/Texture.cpp
  )

add_library(${PROJECT_NAME}
  ${geometry_SRC}
  ${application_SRC}
  ${window_SRC}
  ${events_SRC}
  ${graphics_SRC}
  ${KaliLaska_SRC}
  )
target_compile_features(${PROJECT_NAME}
  PRIVATE
    cxx_std_17
  )
if(NO_ASYNC_LOGGER)
  target_compile_definitions(${PROJECT_NAME}
    PRIVATE
      -DNO_ASYNC_LOGGER
    )
endif()

# because dll can not compile without all dependencies
if(WIN32)
  target_link_libraries(${PROJECT_NAME}
    PRIVATE
      SDL2::SDL2
    )
  target_include_directories(${PROJECT_NAME}
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC
      ${CMAKE_CURRENT_BINARY_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}/../include
    )
else()
  target_link_libraries(${PROJECT_NAME}
    PRIVATE
      Boost::log
      picopng
      -lstdc++fs
    INTERFACE
      SDL2::SDL2
      OpenGL::GL
    )
  target_include_directories(${PROJECT_NAME}
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}
      $<TARGET_PROPERTY:SDL2::SDL2,INTERFACE_INCLUDE_DIRECTORIES>
      $<TARGET_PROPERTY:OpenGL::GL,INTERFACE_INCLUDE_DIRECTORIES>
      ${Boost_INCLUDE_DIRS}
    PUBLIC
      ${CMAKE_CURRENT_BINARY_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}/../include
    )
  # for using boost log
  target_compile_definitions(${PROJECT_NAME}
    PRIVATE
      -DBOOST_LOG_DYN_LINK
    )
endif()

# generate export header
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
generate_export_header(${PROJECT_NAME})
