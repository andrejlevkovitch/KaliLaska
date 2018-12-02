# cmake

cmake_minimum_required(VERSION 3.12)

project(KaliLaska)

include(build.cmake)
include(doxygen.cmake)

set(LIST_SUBDIRS third_party Director)
foreach(DIR ${LIST_SUBDIRS})
  add_subdirectory("src/${DIR}")
endforeach()

message(STATUS "SUBDIRECTORIES: ${LIST_SUBDIRS}")
