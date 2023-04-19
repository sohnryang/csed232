add_library(
  pa3lib
  parser.cpp
  artist.cpp
  classic.cpp
  iclassic.cpp
  sobelx.cpp
  sobely.cpp
  gradient.cpp
  drawer.cpp
  downsample.cpp
  upsample.cpp
  scale.cpp)
target_include_directories(pa3lib PRIVATE "${PA3_ROOT}/include")
add_executable(pa3 main.cpp)
target_include_directories(pa3 PRIVATE "${PA3_ROOT}/include")
target_link_libraries(pa3 PRIVATE pa3lib)
