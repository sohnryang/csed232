if($ENV{BUILD_FUZZ_TESTS})
  add_executable(sptr_fuzz sptr_fuzz.cc)
  target_link_libraries(sptr_fuzz PRIVATE pa4lib)
  target_include_directories(sptr_fuzz PRIVATE "${PA4_ROOT}/include")
  target_compile_options(
    sptr_fuzz PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,fuzzer>")
  target_link_options(sptr_fuzz PRIVATE
                      "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,fuzzer>")
endif()

add_executable(pa4_tests sptr_test.cc image_tests.cc)
target_link_libraries(
  pa4_tests
  PRIVATE pa4lib
  PRIVATE GTest::gtest_main
  PRIVATE GTest::gmock_main)
target_include_directories(pa4_tests PRIVATE "${PA4_ROOT}/include")
include(GoogleTest)
gtest_discover_tests(pa4_tests)
