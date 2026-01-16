cmake_minimum_required(VERSION 3.31)

project(sdl2_graphics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置 Debug 模式的编译选项
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")

find_package(SDL2 REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/math)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/math)
include_directories(${CMAKE_SOURCE_DIR}/src/primitive)

add_executable(sdl2_graphics
        src/main.cpp
        src/sdl2_window.cpp
        src/sdl2_window.h
        src/pixels_buffer.cpp
        src/pixels_buffer.h
        src/primitive/primitive.h
        src/graphics_renderer.cpp
        src/graphics_renderer.h
        src/primitive/point_primitive.cpp
        src/primitive/point_primitive.h
        src/primitive/line_primitive.cpp
        src/primitive/line_primitive.h
        src/primitive/antialiased_line_primitive.cpp
        src/primitive/antialiased_line_primitive.h
        src/primitive/triangle_primitive.cpp
        src/primitive/triangle_primitive.h
)
target_link_libraries(sdl2_graphics PRIVATE SDL2::SDL2)

