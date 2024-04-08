cmake_minimum_required(VERSION 3.27)
project(BasicsOfProgrammingCourse C)

set(CMAKE_C_STANDARD 17)

include ("libs/CMakeLists.txt")

set (files
        "lab_20.c"
        "main.c"
        ${libraries}
)

add_executable (BasicsOfProgrammingCourse ${files})

target_link_libraries(BasicsOfProgrammingCourse -lm)
target_link_libraries(BasicsOfProgrammingCourse ncurses)

target_sources (BasicsOfProgrammingCourse PRIVATE ${files})
source_group (TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${files})