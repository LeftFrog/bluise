cmake_minimum_required(VERSION 3.16)

project(Bluise VERSION 0.5.1 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_SOURCE_DIR}/inc)
link_directories(${CMAKE_SOURCE_DIR}/lib)

include_directories(./main)
link_directories(../build_lib)

set(CMAKE_CXX_COMPILER clang++)

add_executable(bluise starter.cpp ./qt/GameWidget.cpp ./qt/QGame.cpp ./qt/GameListWidget.cpp)

target_link_libraries(bluise PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(bluise PUBLIC ncurses)
target_link_libraries(bluise PUBLIC bluise_core)
