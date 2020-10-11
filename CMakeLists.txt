cmake_minimum_required(VERSION 3.17)
project(gl)

set(CMAKE_CXX_STANDARD 14)




find_package(SDL2 REQUIRED)
message(STATUS "SLD2 included at ${SDL2_INCLUDE_DIRS}")
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(gl main.cpp GameLoop.cpp GameLoop.h common/helperFuncs.h common/helperFuncs.cpp common/SlotMap.h)
target_link_libraries(gl SDL2::SDL2)
