# cmake for Contacts

cmake_minimum_required(VERSION 3.12)

project(Contacts)

set(Contacts_SRC
  "b2ChainAndCircleContact.cpp"
  "b2ChainAndPolygonContact.cpp"
  "b2CircleContact.cpp"
  "b2Contact.cpp"
  "b2ContactSolver.cpp"
  "b2EdgeAndCircleContact.cpp"
  "b2EdgeAndPolygonContact.cpp"
  "b2PolygonAndCircleContact.cpp"
  "b2PolygonContact.cpp"
  )

add_library(${PROJECT_NAME} OBJECT ${Contacts_SRC})
target_compile_options(${PROJECT_NAME} PRIVATE "-std=c++11")
target_sources(${PROJECT_NAME} INTERFACE $<TARGET_OBJECTS:${PROJECT_NAME}>)
