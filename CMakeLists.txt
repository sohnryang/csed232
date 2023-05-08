cmake_minimum_required(VERSION 3.19)

project(CSED232)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1)
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_subdirectory(assignments)
