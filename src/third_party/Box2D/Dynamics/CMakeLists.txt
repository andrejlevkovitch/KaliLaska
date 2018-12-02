# cmake for Dynamics

cmake_minimum_required(VERSION 3.12)

project(Dynamics)

add_subdirectory(Contacts)
add_subdirectory(Joints)

set(Dynamics_SRC
  "b2Body.cpp"
  "b2ContactManager.cpp"
  "b2Fixture.cpp"
  "b2Island.cpp"
  "b2World.cpp"
  "b2WorldCallbacks.cpp"
  )

add_library(${PROJECT_NAME} OBJECT ${Dynamics_SRC})
target_compile_options(${PROJECT_NAME} PRIVATE "-std=c++11")
target_link_libraries(${PROJECT_NAME} INTERFACE Contacts Joints)
target_sources(${PROJECT_NAME} INTERFACE $<TARGET_OBJECTS:${PROJECT_NAME}>)

add_dependencies(${PROJECT_NAME} Contacts)
add_dependencies(${PROJECT_NAME} Joints)
