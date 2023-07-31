cmake_minimum_required(VERSION 3.16)

project(Bluise VERSION 0.4.3 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
)

include_directories(${CMAKE_SOURCE_DIR}/inc)
link_directories(${CMAKE_SOURCE_DIR}/lib)

include_directories(./main)
link_directories(../build_lib)

set(CMAKE_CXX_COMPILER clang++)

add_executable(bluise command_line/command_processor.cpp)

target_link_libraries(bluise bluise-core)
