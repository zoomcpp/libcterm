cmake_minimum_required(VERSION 2.8.11)

add_subdirectory(cterm)

set(sources 
  linux_terminal.cpp 
  linux_window.cpp 
  linux_cursor.cpp
)

add_library(cterm ${sources})

