cmake_minimum_required(VERSION 3.5)

project(EventLogger VERSION 1.0 LANGUAGES CXX)

# Dodaj moduły Qt
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Qt5LinguistTools) # Jeśli potrzebujesz narzędzi do tłumaczenia

# Dodaj źródła
set(SOURCE_FILES
    src/main.cpp
    src/mainwindow.cpp
    src/settings/settingsdialog.cpp
    src/debugwindow/debugwindow.cpp
)

set(UI_FILES
    ui/mainwindow.ui
    ui/settings/settingsdialog.ui
    ui/debugwindow/debugwindow.ui
)

set(RESOURCE_FILES res/icons/resources.qrc)  # Przykładowy plik zasobów

# Dodaj pliki .h do katalogu include
include_directories(include)

# Dodaj plik qmake (.pro) dla Qt Designer
add_executable(EventLogger ${SOURCE_FILES} ${UI_FILES} ${RESOURCE_FILES})

# Link bibliotek Qt
target_link_libraries(EventLogger Qt5::Core Qt5::Gui Qt5::Widgets)

# Przetwarzanie UI i zasobów
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
