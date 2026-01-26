cmake_minimum_required(VERSION 3.31)

project(sdl2_graphics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置编译选项（跨平台）
if(MSVC)
    # MSVC: 使用 UTF-8 编码，禁用警告
    add_compile_options(/utf-8 /W0)
else()
    # GCC/Clang: Debug 模式选项
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -w")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -w")
endif()

# Conan 包管理集成
find_package(SDL2 REQUIRED CONFIG)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/math)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/math)
include_directories(${CMAKE_SOURCE_DIR}/src/primitive)
include_directories(${CMAKE_SOURCE_DIR}/src/image)
include_directories(${CMAKE_SOURCE_DIR}/src/texture)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin/)

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
        src/image/image_loader.cpp
        src/image/image_loader.h
        src/image/image.cpp
        src/image/image.h
        src/texture/texture.cpp
        src/texture/texture.h
)
# Windows 需要链接 SDL2main 来提供正确的入口点
if(WIN32)
    target_link_libraries(sdl2_graphics PRIVATE SDL2::SDL2main SDL2::SDL2-static)
else()
    target_link_libraries(sdl2_graphics PRIVATE SDL2::SDL2-static)
endif()

