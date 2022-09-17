cmake_minimum_required(VERSION 3.23)
project(PolyEditor)

file(GLOB_RECURSE PolyEditor_SRC
        "src/**.h"
        "src/**.cpp"
        )
add_executable(PolyEditor ${PolyEditor_SRC})

target_link_libraries(${PROJECT_NAME} PolyEngine )