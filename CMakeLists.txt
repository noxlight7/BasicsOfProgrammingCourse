cmake_minimum_required(VERSION 3.27)
project(BasicsOfProgrammingCourse C)

set(CMAKE_C_STANDARD 11)

include ("libs/CMakeLists.txt")

set (files
        "main.c"
        ${libraries}
)

add_executable (BasicsOfProgrammingCourse ${files})

target_sources (BasicsOfProgrammingCourse PRIVATE ${files})
source_group (TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${files})