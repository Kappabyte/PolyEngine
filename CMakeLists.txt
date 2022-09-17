cmake_minimum_required(VERSION 3.23)
project(PolyEngine)

add_subdirectory("${PROJECT_SOURCE_DIR}/Projects/PolyEngine" "${PROJECT_SOURCE_DIR}/bin/PolyEngine")
add_subdirectory("${PROJECT_SOURCE_DIR}/Projects/PolyEditor" "${PROJECT_SOURCE_DIR}/bin/PolyEditor")

add_subdirectory("${PROJECT_SOURCE_DIR}/Libraries/glfw" "${PROJECT_SOURCE_DIR}/bin/Libraries/glfw")