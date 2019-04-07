# cmake for test
# if leak_check option on - then test always be faild!

cmake_minimum_required(VERSION 3.10)

project(tests)

# every cpp file - one test
set(TEST_LIST
  src/test_triangulation.cpp
  src/test_TransformMatrix.cpp
  src/test_openGL.cpp
  src/test_Application.cpp
  src/test_Window.cpp
  src/test_CustomEvents.cpp
  src/test_GraphicsScene.cpp
  )

list(LENGTH TEST_LIST TEST_CAPACITY)

message(STATUS "will be generated ${TEST_CAPACITY} tests")

# for cross compile
if (CMAKE_CXX_COMPILER MATCHES "mingw" AND CMAKE_HOST_UNIX)
  set(TEST_RUNNER "wineconsole")
endif()

if(TEST_CAPACITY)
  math(EXPR TEST_LIST_END "${TEST_CAPACITY} - 1")

  foreach(TEST_NUMBER RANGE 0 ${TEST_LIST_END})
    list(GET TEST_LIST ${TEST_NUMBER} TEST_SRC)
    get_filename_component(CUR_TEST ${TEST_SRC} NAME_WE)

    add_executable(${CUR_TEST} ${TEST_SRC})
    target_include_directories(${CUR_TEST}
      PRIVATE
        include
      )
    target_link_libraries(${CUR_TEST}
      PRIVATE
        KaliLaska::KaliLaska
        Catch2::Catch2
        gl3w
      )
    target_compile_features(${CUR_TEST}
      PRIVATE
        cxx_std_17
      )

    # for fix problem with 'too many sections'
    if(CMAKE_CXX_COMPILER MATCHES "mingw")
      target_compile_options(${CUR_TEST}
        PRIVATE
          -Wa,-mbig-obj
        )
    endif()

    add_test(
      NAME
        ${CUR_TEST}
      COMMAND
        ${TEST_RUNNER} $<TARGET_FILE:${CUR_TEST}>
      )
  endforeach()

endif(TEST_CAPACITY)
