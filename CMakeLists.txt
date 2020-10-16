cmake_minimum_required(VERSION 3.17)
project(gl CXX CUDA)

set(CMAKE_CXX_STANDARD 14)


find_package(SDL2 REQUIRED)
message(STATUS "SLD2 included at ${SDL2_INCLUDE_DIRS}")
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(
		gl main.cpp GameLoop.cpp
		GameLoop.h
		common/helperFuncs.h
		common/helperFuncs.cpp
		common/SlotMap.h
		common/CUDARuntime/Particles.cuh
		common/CUDARuntime/Particles.cu
		common/point.h)
target_link_libraries(gl SDL2::SDL2)

set_target_properties( gl
		PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

