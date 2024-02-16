include_directories (${CMAKE_CURRENT_LIST_DIR})

file (GLOB_RECURSE vector ${CMAKE_CURRENT_LIST_DIR}/data_structures/vector/*.[ch])

set (libraries
        ${vector}
)