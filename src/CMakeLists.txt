cmake_minimum_required(VERSION 3.16)

project(Bluise VERSION 0.7 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Concurrent Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Concurrent Sql)

qt_standard_project_setup()

add_subdirectory(QtAwesome QtAwesome)

set(PROJECT_SOURCES
        main.cpp
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

qt_add_executable(Bluise main.cpp
    ./BluiseCore/bluise.cpp 
    ./BluiseCore/Game.cpp 
    ./Widgets/GameOptionsWidget.cpp 
    ./Widgets/EditGameWidget.cpp 
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
    ./Widgets/ScanForGamesWidget.cpp
        BluiseCore/GameScanner.h
        BluiseCore/GameScanner.cpp
        Widgets/ScanForGamesWidget.cpp
        BeautifulUI/OptionButton.cpp
        BeautifulUI/OptionButton.h
        BeautifulUI/AbstractBeautifulButton.cpp
        BeautifulUI/AbstractBeautifulButton.h
)


target_link_libraries(Bluise PRIVATE Qt6::Widgets)
target_link_libraries(Bluise PRIVATE Qt6::Concurrent)
target_link_libraries(Bluise PRIVATE Qt6::Sql)
target_link_libraries(Bluise PUBLIC QtAwesome)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Bluise)
endif()