
set(LLIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/src/llist.c
)

add_library(LLISTLIB OBJECT ${LLIST_SRC})

target_include_directories(LLISTLIB PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)