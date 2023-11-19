
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Macro to add google unit tests
# you may pass include directory as 2nd parameter and library to be linked as 3rd parameter
macro(add_gtest TESTNAME SRC)
  # create an executable in which the tests will be stored
  add_executable(${TESTNAME} ${SRC})

  target_include_directories(${TESTNAME} PUBLIC ${ARGV2})

  # link the Google test infrastructure, mocking library, and a default main function to
  # the test executable.  Remove g_test_main if writing your own main function.
  target_link_libraries(${TESTNAME} ${ARGV3} GTest::gtest_main)
  include(GoogleTest)

  gtest_discover_tests(${TESTNAME}
  )
endmacro()

add_gtest(TEST_void "void.test.cpp" "${CMAKE_SOURCE_DIR}/lib/include" LLISTLIB)
add_gtest(TEST_llist "llist.test.cpp" "${CMAKE_SOURCE_DIR}/lib/include" LLISTLIB)
