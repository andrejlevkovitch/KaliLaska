# cmake for third_party

cmake_minimum_required(VERSION "3.10")

project(third_party)

set(LIST_SUBDIRS gl3w imgui miniz Box2D)
foreach(DIR ${LIST_SUBDIRS})
  add_subdirectory(${DIR})
endforeach()

add_library(base64 "base64/base64.cpp")
target_compile_features(base64 PRIVATE cxx_std_11)
target_include_directories(base64 PUBLIC "base64")

add_library(tinyxml2 "tinyxml2/tinyxml2.cpp")
target_compile_features(tinyxml2 PRIVATE cxx_std_11)
target_include_directories(tinyxml2 PUBLIC "tinyxml2")

# for include picopng
include_directories(picopng)
