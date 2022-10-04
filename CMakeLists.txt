cmake_minimum_required(VERSION 3.23)
project(PolyEngine)
set(CMAKE_CXX_STANDARD 20)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_definitions(Poly_Platform_Windows)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(Poly_Platform_Linux)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_compile_definitions(Poly_Platform_MacOS)
endif()

add_subdirectory("${PROJECT_SOURCE_DIR}/Projects/PolyEngine" "${PROJECT_SOURCE_DIR}/bin/PolyEngine")
add_subdirectory("${PROJECT_SOURCE_DIR}/Projects/PolyEditor" "${PROJECT_SOURCE_DIR}/bin/PolyEditor")

add_subdirectory("${PROJECT_SOURCE_DIR}/Libraries/glfw" "${PROJECT_SOURCE_DIR}/bin/Libraries/glfw")
add_subdirectory("${PROJECT_SOURCE_DIR}/Libraries/Glad" "${PROJECT_SOURCE_DIR}/bin/Libraries/Glad")
add_subdirectory("${PROJECT_SOURCE_DIR}/Libraries/glm" "${PROJECT_SOURCE_DIR}/bin/Libraries/glm")