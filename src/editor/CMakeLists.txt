cmake_minimum_required(VERSION 3.16)

# Configuración del proyecto
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar dependencias
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(SDL2pp REQUIRED)
find_package(yaml-cpp REQUIRED)

# Archivos fuente del editor
set(PROJECT_SOURCES
        leveleditor.cpp
        leveleditor.h
        leveleditor.ui
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

# Configuración del ejecutable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(taller_editor
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
else()
    add_executable(taller_editor
            ${PROJECT_SOURCES}
    )
endif()

# Enlazar librerías
target_link_libraries(taller_editor PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        SDL2pp::SDL2pp
        yaml-cpp
)

# Finalización para Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(taller_editor)
endif()
