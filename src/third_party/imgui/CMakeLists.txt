# imgui

cmake_minimum_required(VERSION "3.10")

project(imgui)

set(IMGUI_SRC
  "sources/imgui.cpp"
  "sources/imgui_demo.cpp"
  "sources/imgui_draw.cpp"
  "sources/imgui_impl_opengl3.cpp"
  "sources/imgui_impl_sdl.cpp"
  "sources/imgui_widgets.cpp"
  )

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

add_library(imgui ${IMGUI_SRC})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
target_include_directories(imgui PUBLIC "include")
target_link_libraries(imgui PRIVATE gl3w)
target_link_libraries(imgui PRIVATE ${SDL2_LIBRARY} ${OPENGL_gl_LIBRARY})
