cmake_minimum_required(VERSION 4.0)

project(glad LANGUAGES C)

add_library(glad STATIC)

target_sources(
    glad
    PRIVATE
    include/KHR/khrplatform.h
    include/glad/gl.h
    src/gl.c
)

target_include_directories(
    glad
    PRIVATE
    include
)
