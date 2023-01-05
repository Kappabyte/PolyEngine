cmake_minimum_required(VERSION 3.23)
project(PolyEngine)


file(GLOB_RECURSE PolyEngine_SRC
        "src/**.h"
        "src/**.cpp"
        )
find_package(OpenGL REQUIRED)

add_library(PolyEngine ${PolyEngine_SRC})

target_include_directories (PolyEngine PUBLIC ${PROJECT_SOURCE_DIR}/src)
include_directories("src")
target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
        glfw
        glm
        Glad
        )