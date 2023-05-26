add_library(pa5lib block.cpp board.cpp logging.cpp game.cpp)
target_include_directories(pa5lib PRIVATE "${PA5_ROOT}/include")
target_compile_features(pa5lib PRIVATE cxx_std_17)

if(DEFINED ENV{CI})
  message(STATUS "CI detected, excluding pa5 target which depends on Qt.")
else()
  find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
  qt_standard_project_setup()

  qt_add_executable(
    pa5
    main.cpp
    mainwindow.cpp
    ../include/mainwindow.h
    blockui.cpp
    ../include/blockui.h
    gameui.cpp
    ../include/gameui.h)
  target_include_directories(pa5 PRIVATE "${PA5_ROOT}/include")
  target_compile_features(pa5 PRIVATE cxx_std_17)
  target_link_libraries(
    pa5
    PRIVATE Qt6::Widgets
    PRIVATE pa5lib)
endif()
