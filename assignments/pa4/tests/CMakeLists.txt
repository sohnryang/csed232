add_executable(sptr_fuzz sptr_fuzz.cc)
target_link_libraries(sptr_fuzz PRIVATE pa4lib)
target_include_directories(sptr_fuzz PRIVATE "${PA4_ROOT}/include")
target_compile_options(
  sptr_fuzz PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,fuzzer>")
target_link_options(sptr_fuzz PRIVATE
                    "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,fuzzer>")
