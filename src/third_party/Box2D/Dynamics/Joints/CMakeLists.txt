# cmake for Joints

cmake_minimum_required(VERSION 3.12)

project(Joints)

set(Joints_SRC
  "b2DistanceJoint.cpp"
  "b2FrictionJoint.cpp"
  "b2GearJoint.cpp"
  "b2Joint.cpp"
  "b2MotorJoint.cpp"
  "b2MouseJoint.cpp"
  "b2PrismaticJoint.cpp"
  "b2PulleyJoint.cpp"
  "b2RevoluteJoint.cpp"
  "b2RopeJoint.cpp"
  "b2WeldJoint.cpp"
  "b2WheelJoint.cpp"
  )

add_library(${PROJECT_NAME} OBJECT ${Joints_SRC})
target_compile_options(${PROJECT_NAME} PRIVATE "-std=c++11")
target_sources(${PROJECT_NAME} INTERFACE $<TARGET_OBJECTS:${PROJECT_NAME}>)
