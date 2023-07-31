cmake_minimum_required(VERSION 3.16)

project(bluise-core VERSION 0.4.3 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    bluise.cpp
    Game.cpp 
    GLLReader.cpp
)

set(CMAKE_CXX_COMPILER clang++)

add_library(bluise-core SHARED ${PROJECT_SOURCES})
set_target_properties(bluise-core PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(bluise-core PROPERTIES PUBLIC_HEADER bluise.h)
target_include_directories(bluise-core PUBLIC .)