# cmake for window example

project(scene_view)

set(WINDOW_SRC
  ExampleItem.cpp
  ExampleScene.cpp
  ExampleView.cpp
  main.cpp
  )

add_executable(${PROJECT_NAME} ${WINDOW_SRC})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    KaliLaska::KaliLaska
    gl3w
  )
