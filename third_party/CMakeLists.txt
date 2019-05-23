# cmake for third_party

# init and update submodules if they not init at the moment
if(NOT EXISTS Box2D)
  find_package(Git REQUIRED)
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule init)
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule update)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(picopng)
add_library(picopng INTERFACE)
target_include_directories(picopng INTERFACE picopng)

add_library(base64 STATIC "base64/base64.cpp")
target_include_directories(base64 INTERFACE "base64")

set(miniz_SRC
  miniz/miniz.c
  miniz/miniz_tdef.c
  miniz/miniz_tinfl.c
  miniz/miniz_zip.c
  )
add_library(miniz STATIC ${miniz_SRC})
target_include_directories(miniz INTERFACE "miniz")

set(imgui_SRC
  imgui/imgui.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_demo.cpp
  imgui/imgui_widgets.cpp
  imgui/imgui_impl_opengl3.cpp
  imgui/imgui_impl_sdl.cpp
  )
add_library(imgui SHARED ${imgui_SRC})
target_include_directories(imgui INTERFACE "imgui")
if (WIN32)
  target_link_libraries(imgui
    PRIVATE
      SDL2::SDL2
      OpenGL::GL
    )
elseif()
  target_link_libraries(imgui
    INTERFACE
      SDL2::SDL2
      OpenGL::GL
    )
endif()
target_include_directories(imgui
  PRIVATE
    $<TARGET_PROPERTY:SDL2::SDL2,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:OpenGL::GL,INTERFACE_INCLUDE_DIRECTORIES>
  )
target_compile_definitions(imgui
  PRIVATE
    -DUSE_GL_ES3
  )

add_subdirectory(Box2D)
add_subdirectory(Catch2)
