cmake_minimum_required(VERSION 3.16)

project(Bluise VERSION 0.6.4 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH /Users/Shared/Qt/6.7.0/macos/lib/cmake/)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()


set(PROJECT_SOURCES
    starter.cpp
    bluise.h
    bluise.cpp
    bluise_error.h
    command_processor.cpp
    Game.h
    Game.cpp
    gll_syntax_error.h
    invalid_path.h
    GLLReader.h
    GLLReader.cpp

)

qt_add_executable(bluise starter.cpp 
    bluise.cpp 
    Game.cpp 
    GameOptionsWidget.cpp 
    GameEditWidget.cpp 
    GameListModel.cpp
    CoverDelegate.cpp
    GameInfoWidget.cpp
    ChoosePictureWidget.cpp 
    FileValidator.cpp 
    GameOptionWidget.cpp 
    GameAddWidget.cpp
    MainWindow.cpp
    ToolBar.cpp
    GameProxyModel.cpp
    GameInfoWidget.ui
)

# set_target_properties(bluise PROPERTIES
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

target_link_libraries(bluise PRIVATE Qt6::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(bluise)
endif()