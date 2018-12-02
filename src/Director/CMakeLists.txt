# cmake for Director

cmake_minimum_required(VERSION 3.12)

project(Director)

set(Director_SRC
  "sources/Director.cpp"
  )

add_library(${PROJECT_NAME} ${Director_SRC})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC "include")
