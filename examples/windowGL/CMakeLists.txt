# cmake for window example

project(windowGL)

set(WINDOW_SRC
  WindowGL.cpp
  main.cpp
  )

add_executable(${PROJECT_NAME} ${WINDOW_SRC})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    KaliLaska::KaliLaska
  )
