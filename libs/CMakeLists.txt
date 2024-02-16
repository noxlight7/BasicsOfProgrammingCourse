include_directories (${CMAKE_CURRENT_LIST_DIR})

file (GLOB_RECURSE vector ${CMAKE_CURRENT_LIST_DIR}/data_structures/vector/*.[ch])
file (GLOB_RECURSE array ${CMAKE_CURRENT_LIST_DIR}/data_structures/array/*.[ch])

set (libraries
        ${vector}
        ${array}
)