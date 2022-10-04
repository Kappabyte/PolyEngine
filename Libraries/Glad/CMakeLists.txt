cmake_minimum_required(VERSION 3.23)
project(Glad)

find_package(OpenGL REQUIRED)

add_library(Glad src/glad.c)

target_include_directories (Glad PUBLIC ${PROJECT_SOURCE_DIR}/include)
include_directories("include")