# cmake

cmake_minimum_required(VERSION 3.12)

project(KaliLaska)

include(cmake/build.cmake)
include(cmake/doxygen.cmake)

find_package(OpenGL REQUIRED)
find_package(gl3w REQUIRED)
find_package(SDL2 REQUIRED)
find_package(tinyxml2 REQUIRED)

set(LIST_SUBDIRS third_party src tests examples)
foreach(DIR ${LIST_SUBDIRS})
  add_subdirectory(${DIR})
endforeach()

add_library(KaliLaska::KaliLaska ALIAS ${PROJECT_NAME})

message(STATUS "SUBDIRECTORIES: ${LIST_SUBDIRS}")
