cmake_minimum_required(VERSION 3.16)

project(Bluise VERSION 0.4 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    main.cpp
    Game.h 
    Game.cpp 
    GLLReader.cpp
    invalid_path.h 
)

add_compile_options(-lncurses)

include_directories(${CMAKE_SOURCE_DIR}/inc)
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_CXX_COMPILER clang++)

add_executable(bluise main.cpp GLLReader.cpp Game.h Game.cpp  invalid_path.h GameLine.h GameLine.cpp Menu.h Menu.cpp)

target_link_libraries(bluise ncurses)