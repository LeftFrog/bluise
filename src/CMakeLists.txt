cmake_minimum_required(VERSION 3.16)

project(GameLauncher VERSION 0.1.8 LANGUAGES CXX C)

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

add_executable(GameLauncher main.cpp Game.h Game.cpp GLLReader.cpp invalid_path.h)