# cmake for Collisions

cmake_minimum_required(VERSION 3.12)

project(Collision)

add_subdirectory(Shapes)

set(Collision_SRC
    "b2BroadPhase.cpp"
    "b2CollideCircle.cpp"
    "b2CollideEdge.cpp"
    "b2CollidePolygon.cpp"
    "b2Collision.cpp"
    "b2Distance.cpp"
    "b2DynamicTree.cpp"
    "b2TimeOfImpact.cpp"
  )

add_library(${PROJECT_NAME} OBJECT ${Collision_SRC})
target_compile_options(${PROJECT_NAME} PRIVATE "-std=c++11")
target_include_directories(${PROJECT_NAME} PUBLIC "../../")
target_link_libraries(${PROJECT_NAME} INTERFACE Shapes)
target_sources(${PROJECT_NAME} INTERFACE $<TARGET_OBJECTS:${PROJECT_NAME}>)

add_dependencies(${PROJECT_NAME} Shapes)
