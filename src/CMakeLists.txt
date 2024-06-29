cmake_minimum_required(VERSION 3.16)

project(Bluise VERSION 0.6.4 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH /Users/Shared/Qt/6.7.2/macos/lib/cmake/)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_subdirectory(QtAwesome QtAwesome)

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

qt_add_executable(Bluise starter.cpp 
    ./BluiseCore/bluise.cpp 
    ./BluiseCore/Game.cpp 
    ./Widgets/GameOptionsWidget.cpp 
    ./Widgets/GameEditWidget.cpp 
    ./ModelView/GameListModel.cpp
    ./ModelView/CoverDelegate.cpp
    ./Widgets/GameInfoWidget.cpp
    ./Widgets/ChoosePictureWidget.cpp 
    ./BluiseCore/FileValidator.cpp 
    ./Widgets/GameOptionWidget.cpp 
    ./Widgets/AddLocalInstalledGameWidget.cpp
    MainWindow.cpp
    ./Widgets/ToolBar.cpp
    ./ModelView/GameProxyModel.cpp
    ./Widgets/GameInfoWidget.ui
    ./BeautifulUI/BeautifulButton.cpp
    ./BeautifulUI/BeautifulButtonGroup.cpp
    ./Widgets/SearchBar.cpp
    ./Widgets/BoxOptionWidget.cpp
    ./Widgets/AddGameWidget.cpp
)

# set_target_properties(Bluise PROPERTIES
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

target_link_libraries(Bluise PRIVATE Qt6::Widgets)
target_link_libraries(Bluise PUBLIC QtAwesome)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Bluise)
endif()