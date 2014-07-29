cmake_minimum_required(VERSION 2.8.11)

set(sources linux_terminal.cpp linux_window.cpp)
add_library(cterm ${sources})

add_executable(ctermx main.cpp ${sources})
