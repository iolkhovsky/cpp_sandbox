cmake_minimum_required(VERSION 3.5)

project(DemoApp)

add_library(funclib SHARED functions.cpp)
target_include_directories(funclib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(demo_app main.cpp)

target_link_libraries(demo_app PRIVATE funclib)
