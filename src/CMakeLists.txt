# cmake for src

include(GenerateExportHeader)

set(KaliLaska_SRC
  core/Point.cpp
  core/Size.cpp
  core/Color.cpp
  core/Box.cpp


  application/EventNotifyer.cpp
  application/Application.cpp
  application/AppFactory.cpp

  application/sdl/ApplicationSdl.cpp


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


  window/Window.cpp

  window/sdl/WindowSdl.cpp
  window/sdl/WindowSdlFactory.cpp

  opengl/ShaderProgram.cpp
  opengl/Renderer.cpp

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

add_library(${PROJECT_NAME} ${KaliLaska_SRC})
target_compile_features(${PROJECT_NAME}
  PRIVATE
    cxx_std_17
  )

# because dll can not compile without all dependencies
if(WIN32)
  target_link_libraries(${PROJECT_NAME}
    PRIVATE
      SDL2::SDL2
      gl3w
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
    INTERFACE
      SDL2::SDL2
      gl3w
    )
  target_include_directories(${PROJECT_NAME}
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}
      $<TARGET_PROPERTY:SDL2::SDL2,INTERFACE_INCLUDE_DIRECTORIES>
      $<TARGET_PROPERTY:gl3w,INTERFACE_INCLUDE_DIRECTORIES>
      ${Boost_INCLUDE_DIRS}
    PUBLIC
      ${CMAKE_CURRENT_BINARY_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}/../include
    )
endif()

# generate export header
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
generate_export_header(${PROJECT_NAME})
