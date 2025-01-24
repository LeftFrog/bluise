cmake_minimum_required(VERSION 3.16)

project(Bluise VERSION 0.7.3 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Concurrent Sql Network NetworkAuth)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Concurrent Sql Network NetworkAuth)

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
    BluiseCore/IconHandler.cpp
    BluiseCore/IconHandler.h
    Widgets/AddGameOptionsWidget.cpp
    Widgets/AddGameOptionsWidget.h
    BeautifulUI/MenuButton.cpp
    BeautifulUI/MenuButton.h
    Sync/GoogleDriveManager.cpp
    Sync/GoogleDriveManager.h
    Widgets/SettingsWidget.cpp
    Widgets/SettingsWidget.h
    BluiseCore/Settings.cpp
    BluiseCore/Settings.h
    Sync/UploadWorker.h
    Sync/UploadWorker.cpp
    MacWindowHandler.mm
)


target_link_libraries(Bluise PRIVATE Qt6::Widgets)
target_link_libraries(Bluise PRIVATE Qt6::Concurrent)
target_link_libraries(Bluise PRIVATE Qt6::Sql)
target_link_libraries(Bluise PUBLIC QtAwesome)
target_link_libraries(Bluise PRIVATE Qt6::Network)
target_link_libraries(Bluise PRIVATE Qt6::NetworkAuth)
target_link_libraries(Bluise PRIVATE "-framework Cocoa")