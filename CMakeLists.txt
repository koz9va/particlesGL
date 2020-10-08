cmake_minimum_required(VERSION 3.17)
project(gl)

set(CMAKE_CXX_STANDARD 14)


find_package(Boost REQUIRED)
message(STATUS "Boost included at ${Boost_INCLUDE_DIRS}")
find_package(OpenGL REQUIRED)
message(STATUS "OpenGl included at ${OPENGL_LIBRARIES}")

include_directories(${Boost_INCLUDE_DIRS}, ${OPENGL_FOUND})
add_executable(gl main.cpp common/Shader.hpp common/loadShader.cpp GameLoop.cpp GameLoop.h)
target_link_libraries(gl ${Boost_LIBRARIES})
target_link_libraries(gl ${OPENGL_LIBRARIES})
target_link_libraries(gl GLEW)
target_link_libraries(gl glfw)