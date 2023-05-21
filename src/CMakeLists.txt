cmake_minimum_required(VERSION 3.16)

project(Bluise VERSION 0.3.4 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    main.cpp 
    Game.h 
    Game.cpp 
    GLLReader.cpp
    invalid_path.h 
)

set(CMAKE_CXX_COMPILER clang++)

add_executable(bluise main.cpp GLLReader.cpp Game.h Game.cpp  invalid_path.h)