cmake_minimum_required(VERSION 3.16)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(yaml-cpp REQUIRED)

set(PROJECT_SOURCES
    leveleditor.cpp
    leveleditor.h
    leveleditorcontroller.cpp
    leveleditorcontroller.h
    pathmaker.cpp
    pathmaker.h
    idmaker.cpp
    idmaker.h
    mapobject.cpp
    mapobject.h
    typemaker.cpp
    typemaker.h
    main.cpp
)

add_executable(taller_editor ${PROJECT_SOURCES})

target_link_libraries(taller_editor PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    yaml-cpp
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(taller_editor)
endif()

