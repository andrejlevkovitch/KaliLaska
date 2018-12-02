# cmake for objects

cmake_minimum_required(VERSION 3.12)

project(objects)

set(objects_SRC

  )

add_library(${PROJECT_NAME} ${objects_SRC})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC "include")
