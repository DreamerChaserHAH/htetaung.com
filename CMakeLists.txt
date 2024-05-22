cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wno-narrowing")
project(portfolio)

add_subdirectory(raylib)

include_directories(src raylib/src raygui/src)

add_executable(portfolio src/main.cpp)

target_link_libraries(portfolio raylib)
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})