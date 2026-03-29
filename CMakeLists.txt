cmake_minimum_required(VERSION 3.20)
project(MySharedPointerTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(my_shared_pointer_tests
  tests/test_construction.cpp
  tests/test_copy_move.cpp
  tests/test_assignment.cpp
  tests/test_reset.cpp
  tests/test_access.cpp
  tests/test_factory.cpp
  tests/test_destruction.cpp
)

target_include_directories(my_shared_pointer_tests PRIVATE include)

target_link_libraries(my_shared_pointer_tests PRIVATE GTest::gtest_main)

gtest_discover_tests(my_shared_pointer_tests)
