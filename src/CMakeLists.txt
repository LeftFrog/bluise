cmake_minimum_required(VERSION 3.16)

project(Bluise VERSION 0.4.3 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    main/bluise.cpp
    main/Game.h 
    main/Game.cpp 
    main/GLLReader.cpp
    maininvalid_path.h 
)

add_compile_options(-lncurses)

include_directories(${CMAKE_SOURCE_DIR}/inc)
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_CXX_COMPILER clang++)

add_executable(bluise main/bluise_error.h main/bluise.cpp main/bluise.h main/GLLReader.cpp main/Game.h main/Game.cpp  command_line/command_processor.h command_line/command_processor.cpp main/invalid_path.h command_line_ui/GameLine.h command_line_ui/GameLine.cpp command_line_ui/Menu.h command_line_ui/Menu.cpp)

target_link_libraries(bluise ncurses)