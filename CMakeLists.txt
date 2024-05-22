cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wno-narrowing")
project(portfolio)

include_directories(src raylib/src raygui/src)
add_executable(portfolio src/main.cpp)
add_library(projects src/projects.cpp)
add_library(menu src/menu.cpp)
add_library(text src/text.cpp)

if(EMSCRIPTEN)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s ERROR_ON_UNDEFINED_SYMBOLS=0 -sALLOW_MEMORY_GROWTH --bind --memory")
set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.

find_library(RL_LIBRARY NAMES raylib PATHS raylib/src NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
set_target_properties(portfolio PROPERTIES LINK_FLAGS "--preload-file ${CMAKE_SOURCE_DIR}/resources@resources")
target_link_libraries(portfolio ${RL_LIBRARY})
else()
add_subdirectory(raylib)
target_link_libraries(portfolio raylib)
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
endif()
target_link_libraries(portfolio projects menu text)