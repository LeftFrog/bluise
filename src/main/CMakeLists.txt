cmake_minimum_required(VERSION 3.16)

project(bluise_core VERSION 0.5 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    bluise.h
    Game.h
    GLLReader.h
    bluise_error.h
    gll_syntax_error.h
    invalid_path.h
    bluise.cpp
    Game.cpp 
    GLLReader.cpp
)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(CMAKE_CXX_COMPILER g++)

add_library(bluise_core SHARED ${PROJECT_SOURCES})
target_link_libraries(bluise_core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
set_target_properties(bluise_core PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(bluise_core PROPERTIES PUBLIC_HEADER bluise.h)
target_include_directories(bluise_core PUBLIC .)