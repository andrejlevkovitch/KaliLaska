# cmake for examples

set(LIST_SUBDIRS window windowGL scene_view textures)

foreach(DIR ${LIST_SUBDIRS})
  add_subdirectory(${DIR})
endforeach()
