# cmake for Shapes

cmake_minimum_required(VERSION 3.12)

project(Shapes)

set(Shapes_SRC
    "b2ChainShape.cpp"
    "b2CircleShape.cpp"
    "b2EdgeShape.cpp"
    "b2PolygonShape.cpp"
  )

add_library(${PROJECT_NAME} OBJECT ${Shapes_SRC})
target_compile_options(${PROJECT_NAME} PRIVATE "-std=c++11")
target_sources(${PROJECT_NAME} INTERFACE $<TARGET_OBJECTS:${PROJECT_NAME}>)
