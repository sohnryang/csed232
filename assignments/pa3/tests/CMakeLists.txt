add_executable(pa3_tests artist_test.cpp drawer_test.cpp parser_test.cpp)
target_link_libraries(
  pa3_tests
  PRIVATE pa3lib
  PRIVATE GTest::gtest_main)
target_include_directories(pa3_tests PRIVATE "${PA3_ROOT}/include")
target_compile_options(
  pa3_tests PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,leak>")
target_link_options(pa3_tests PRIVATE
                    "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,leak>")
include(GoogleTest)
gtest_discover_tests(pa3_tests)
