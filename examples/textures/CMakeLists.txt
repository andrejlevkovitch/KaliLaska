# cmake for textures example

cmake_minimum_required(VERSION 3.12)

project(textures)

set(textures_SRC
  main.cpp
  TextureItem.cpp
  View.cpp
  Scene.cpp
  )

add_executable(${PROJECT_NAME} ${textures_SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE KaliLaska::KaliLaska)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

configure_file("shaders.hpp.cmake" "${CMAKE_CURRENT_BINARY_DIR}/shaders.hpp")
