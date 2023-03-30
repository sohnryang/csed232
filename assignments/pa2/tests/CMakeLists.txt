include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(pa2_tests linked_list_test.cpp)
target_link_libraries(pa2_tests PRIVATE pa2lib PRIVATE GTest::gtest_main)
target_include_directories(pa2_tests PRIVATE "${PA2_ROOT}/include")
target_compile_options(pa2_tests PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,leak>")
target_link_options(pa2_tests PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,leak>")
include(GoogleTest)
gtest_discover_tests(pa2_tests)
