# cmake for examples

set(LIST_SUBDIRS window windowGL)

foreach(DIR ${LIST_SUBDIRS})
  add_subdirectory(${DIR})
endforeach()
