# cmake for window example

project(scene_view)

set(WINDOW_SRC
  ExampleItem.cpp
  ExampleScene.cpp
  ExampleView.cpp
  RingItem.cpp
  #TextureItem.cpp
  main.cpp
  )

add_executable(${PROJECT_NAME} ${WINDOW_SRC})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    KaliLaska::KaliLaska
  )
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

configure_file("shaders.hpp.cmake" "${CMAKE_CURRENT_BINARY_DIR}/shaders.hpp")
