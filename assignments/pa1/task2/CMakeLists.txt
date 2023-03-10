project(pa1_task2)
add_executable(pa1_task2 task2.cpp)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT pa1_task2)
