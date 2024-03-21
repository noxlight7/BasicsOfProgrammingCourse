include_directories (${CMAKE_CURRENT_LIST_DIR})

file (GLOB_RECURSE ../data_structures/string ../data_structures/string/*.[ch])

set (libraries
        ${string}
)