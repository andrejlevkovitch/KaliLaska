# cmake for third_party

# for include picopng
include_directories(picopng)

find_package(OpenGL REQUIRED)

if(NOT EXISTS Box2D)
  find_package(Git REQUIRED)
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule init)
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule update)
endif()

add_library(base64 "base64/base64.cpp")
target_include_directories(base64 PUBLIC "base64")

set(miniz_SRC
  miniz/miniz.c
  miniz/miniz_tdef.c
  miniz/miniz_tinfl.c
  miniz/miniz_zip.c
  )
add_library(miniz ${miniz_SRC})
target_include_directories(miniz PUBLIC "miniz")

set(imgui_SRC
  imgui/imgui.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_demo.cpp
  imgui/imgui_widgets.cpp
  imgui/imgui_impl_opengl3.cpp
  imgui/imgui_impl_sdl.cpp
  )
add_library(imgui ${imgui_SRC})
target_include_directories(imgui PUBLIC "imgui")
target_link_libraries(imgui PRIVATE SDL2::SDL2 gl3w)

add_subdirectory(Box2D)
