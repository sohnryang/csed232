add_executable(sptr_fuzz sptr_fuzz.cc)
target_link_libraries(sptr_fuzz PRIVATE pa4lib)
target_include_directories(sptr_fuzz PRIVATE "${PA4_ROOT}/include")
target_compile_options(
  sptr_fuzz PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,fuzzer>")
target_link_options(sptr_fuzz PRIVATE
                    "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,fuzzer>")

add_executable(pa4_tests sptr_test.cc image_tests.cc)
target_link_libraries(
  pa4_tests
  PRIVATE pa4lib
  PRIVATE GTest::gtest_main
  PRIVATE GTest::gmock_main)
target_include_directories(pa4_tests PRIVATE "${PA4_ROOT}/include")
target_compile_options(
  pa4_tests PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,leak>")
target_link_options(pa4_tests PRIVATE
                    "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,leak>")
include(GoogleTest)
gtest_discover_tests(pa4_tests)
