include_directories (${CMAKE_CURRENT_LIST_DIR})

file (GLOB_RECURSE vector ${CMAKE_CURRENT_LIST_DIR}/vector/*.[ch])
file (GLOB_RECURSE vector_void ${CMAKE_CURRENT_LIST_DIR}/vector_void/*.[ch])
file (GLOB_RECURSE array ${CMAKE_CURRENT_LIST_DIR}/array/*.[ch])
file (GLOB_RECURSE matrix ${CMAKE_CURRENT_LIST_DIR}/matrix/*.[ch])
file (GLOB_RECURSE string ${CMAKE_CURRENT_LIST_DIR}/string/*.[ch])
file (GLOB_RECURSE polynomial ${CMAKE_CURRENT_LIST_DIR}/polynomial/*.[ch])
file (GLOB_RECURSE storehouse ${CMAKE_CURRENT_LIST_DIR}/storehouse/*.[ch])

set (libraries
        ${vector}
        ${vector_void}
        ${array}
        ${matrix}
        ${string}
        ${polynomial}
        ${storehouse}
)