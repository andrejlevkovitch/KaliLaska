# cmake for Scene

cmake_minimum_required(VERSION 3.12)

project(Scene)

set(Scene_SRC
  "sources/Scene.cpp"
  )

add_library(${PROJECT_NAME} ${Scene_SRC})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC "include")
