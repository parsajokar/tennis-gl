cmake_minimum_required(VERSION 4.0)

project(tennis-gl LANGUAGES C)

add_executable(tennis-gl)

target_sources(
    tennis-gl
    PRIVATE
    src/main.c
)
