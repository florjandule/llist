cmake_minimum_required(VERSION 3.14.0)

project(LLIST
    VERSION 00.01.00
    DESCRIPTION "Linked List Library"
    LANGUAGES C
    HOMEPAGE_URL "https://github.com/florjandule/llist.git"
)

# Set Build Options if this is the root project
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
    # Set the C standard to C99
    set(CMAKE_C_STANDARD 99)

    # Set the compiler flags
    if(NOT MSVC)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall -Wextra")
    endif()
    # Build samples
    add_subdirectory(samples)
endif()

add_subdirectory(lib)
