cmake_minimum_required(VERSION 3.16)

project(Bluise VERSION 0.6.3 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH /Users/Shared/Qt/6.6.2/macos/lib/cmake/)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Quick QuickWidgets)

qt_standard_project_setup()


qt_add_qml_module(appBluise_qml
    URI Bluise_qml
    VERSION 1.0
    QML_FILES GameWidget.qml
)

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

qt_add_executable(bluise starter.cpp bluise.cpp Game.cpp GameWidget.cpp GameListWidget.cpp GameOptionsWidget.cpp GameEditWidget.cpp ChoosePictureWidget.cpp FileValidator.cpp GameOptionWidget.cpp GameAddWidget.cpp)

target_link_libraries(bluise PRIVATE Qt6::Widgets)
target_link_libraries(bluise PRIVATE Qt6::Quick)
target_link_libraries(bluise PRIVATE Qt6::QuickWidgets)

