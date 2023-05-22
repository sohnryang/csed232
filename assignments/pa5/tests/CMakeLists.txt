add_executable(pa5_tests board_test.cpp)
target_compile_features(pa5_tests PRIVATE cxx_std_17)
target_link_libraries(
  pa5_tests
  PRIVATE pa5lib
  PRIVATE GTest::gtest_main
  PRIVATE GTest::gmock_main)
target_include_directories(pa5_tests PRIVATE "${PA5_ROOT}/include")
target_compile_options(
  pa5_tests PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,leak>")
target_link_options(pa5_tests PRIVATE
                    "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,leak>")
include(GoogleTest)
gtest_discover_tests(pa5_tests)

add_executable(board_fuzz board_fuzz.cpp)
target_compile_features(board_fuzz PRIVATE cxx_std_17)
target_link_libraries(board_fuzz PRIVATE pa5lib)
target_include_directories(board_fuzz PRIVATE "${PA5_ROOT}/include")
target_compile_options(
  board_fuzz PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,fuzzer>")
target_link_options(board_fuzz PRIVATE
                    "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,fuzzer>")
