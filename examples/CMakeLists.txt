# cmake for examples

set(LIST_SUBDIRS window windowGL windowTmp scene_view)

foreach(DIR ${LIST_SUBDIRS})
  add_subdirectory(${DIR})
endforeach()
