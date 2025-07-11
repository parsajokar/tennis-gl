cmake_minimum_required(VERSION 4.0)

set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory(lib/glfw)

project(tennis-gl LANGUAGES C)

add_executable(tennis-gl)

target_sources(
    tennis-gl
    PRIVATE
    src/main.c
    src/game.h
    src/game.c
)

target_include_directories(
    tennis-gl
    PRIVATE
    lib/glfw/include
)

target_link_libraries(
    tennis-gl
    PRIVATE
    glfw
    GL
)
