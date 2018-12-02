# cmake for Box2D

cmake_minimum_required(VERSION 3.12)

project(Box2D)

add_compile_options("-fPIC")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../")

set(LIST_SUBDIRS Collision Common Dynamics Rope)
message(STATUS "SUBDIRECTORIES: ${LIST_SUBDIRS}")

foreach(DIR ${LIST_SUBDIRS})
  add_subdirectory("${DIR}")
endforeach()

add_library(${PROJECT_NAME}
  $<TARGET_OBJECTS:Collision>
  $<TARGET_OBJECTS:Common>
  $<TARGET_OBJECTS:Dynamics>
  $<TARGET_OBJECTS:Rope>
  )
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
target_link_libraries(${PROJECT_NAME} PRIVATE Collision Common Dynamics Rope)
target_include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/../")
