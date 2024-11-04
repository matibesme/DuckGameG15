cmake_minimum_required(VERSION 3.13)

if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

project(taller_tp
    VERSION 1.0
    HOMEPAGE_URL "https://github.com/URL-HERE"
    LANGUAGES CXX
    )

option(TALLER_TESTS "Enable / disable tests." ON)
option(TALLER_CLIENT "Enable / disable client program." ON)
option(TALLER_SERVER "Enable / disable server program." ON)
option(TALLER_EDITOR "Enable / disable editor program." ON)
option(TALLER_MAKE_WARNINGS_AS_ERRORS "Enable / disable warnings as errors." ON)

message(CMAKE_CXX_COMPILER_ID="${CMAKE_CXX_COMPILER_ID}")

# Define target: lib common between client, server and editor programs
# HEY TODO XXX: change the name to something that you like
add_library(taller_common STATIC)

# add the source files that make the lib
# HEY!! TODO XXX: add more subfolders here
add_subdirectory(common/)


# set compiler warnings to the targets
include(cmake/CompilerWarnings.cmake)
set_project_warnings(taller_common ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

# Say where the headers will be found required by library target
# Make this PUBLIC so any dependant linking lib will inherit this
# location (so our dependants will not have to explicitly request this)
target_include_directories(taller_common PUBLIC .)

# Install libSDL2pp (for client or editor)
# HEY!! TODO XXX: add more dependendies (either for client, server or editor)
if(TALLER_CLIENT OR TALLER_EDITOR)
    include(FetchContent)
    FetchContent_Declare(
        libSDL2pp
        URL https://github.com/libSDL2pp/libSDL2pp/archive/cc198c9a5657048bee67ece82de620b2d5661084.zip
    )

    FetchContent_MakeAvailable(libSDL2pp)
endif()

# Program section
# ---------------
if(TALLER_CLIENT)
    # Cambiar el nombre del ejecutable si es necesario
    add_executable(taller_client)
    find_package(SDL2_image REQUIRED)
    add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")

    # Incluir directorios 'client' y 'common' para los archivos de encabezado
    include_directories(${CMAKE_SOURCE_DIR}/client)
    include_directories(${CMAKE_SOURCE_DIR}/common)
    include_directories(${CMAKE_SOURCE_DIR}/client/items)


    # Incluir automáticamente todos los archivos .cpp y .h de las carpetas 'client' y 'common'
    file(GLOB_RECURSE CLIENT_SOURCES
            "${CMAKE_SOURCE_DIR}/client/*.cpp"
            "${CMAKE_SOURCE_DIR}/client/*.h"
    )

    file(GLOB COMMON_SOURCES
            "${CMAKE_SOURCE_DIR}/common/*.cpp"
            "${CMAKE_SOURCE_DIR}/common/*.h"
    )

    # Agregar los archivos fuentes de 'client' y 'common' al ejecutable
    target_sources(taller_client PRIVATE ${CLIENT_SOURCES} ${COMMON_SOURCES})

    # Hacer que dependa de la biblioteca común y SDL2pp
    add_dependencies(taller_client taller_common SDL2pp::SDL2pp)

    # Añadir advertencias al proyecto
    set_project_warnings(taller_client ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # Incluir las cabeceras de la biblioteca libSDL2pp
    target_include_directories(taller_client PRIVATE ${libSDL2pp_SOURCE_DIR})

    # Enlazar la biblioteca común y SDL2pp al ejecutable del cliente
    target_link_libraries(taller_client taller_common SDL2pp::SDL2pp SDL2_image::SDL2_image)
endif()

if(TALLER_SERVER)
    # Cambiar el nombre del ejecutable si es necesario
    add_executable(taller_server
            server
            server/items/weapons/cowboy_pistol.h
            server/items/weapons/duel_pistol.cpp
            server/items/weapons/magnum.cpp
            server/items/weapons/cowboy_pistol.cpp
            server/duck_action.cpp
    )

    # Incluir el directorio 'server' para los archivos de encabezado (opcional)
    include_directories(${CMAKE_SOURCE_DIR}/server)
    include_directories(${CMAKE_SOURCE_DIR}/common)


    # Incluir automáticamente todos los archivos .cpp y .h de la carpeta 'server'
    file(GLOB SERVER_SOURCES
            "${CMAKE_SOURCE_DIR}/server/*.cpp"
            "${CMAKE_SOURCE_DIR}/server/*.h"
    )

    file(GLOB COMMON_SOURCES
            "${CMAKE_SOURCE_DIR}/common/*.cpp"
            "${CMAKE_SOURCE_DIR}/common/*.h"
    )

    # Agregar los archivos fuentes al ejecutable
    target_sources(taller_server PRIVATE ${SERVER_SOURCES} ${COMMON_SOURCES})

    # Hacer que dependa de la biblioteca común
    add_dependencies(taller_server taller_common)

    # Add source files and enable warnings
    # HEY!! TODO XXX: add more subfolders here
    add_subdirectory(server)

    set_project_warnings(taller_server ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)


    # Link the taller_common lib target
    target_link_libraries(taller_server taller_common yaml-cpp)
endif()

if(TALLER_EDITOR)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

    set(PROJECT_SOURCES
        editor/levelEditor/leveleditor.cpp  
        editor/levelEditor/leveleditor.h
        editor/levelEditor/leveleditor.ui
        editor/levelEditor/leveleditorcontroller.cpp
        editor/levelEditor/leveleditorcontroller.h
        editor/levelEditor/pathmaker.h
        editor/levelEditor/pathmaker.cpp
        editor/levelEditor/idmaker.h
        editor/levelEditor/idmaker.cpp
        editor/levelEditor/mapobject.h
        editor/levelEditor/mapobject.cpp
        editor/levelEditor/main.cpp
    )

    if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(taller_editor
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
        )
    else()
        if(ANDROID)
            add_library(taller_editor SHARED
                ${PROJECT_SOURCES}
            )
        else()
            add_executable(taller_editor
                ${PROJECT_SOURCES}
            )
        endif()
    endif()

    target_link_libraries(taller_editor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets taller_common SDL2pp::SDL2pp yaml-cpp)

    set_target_properties(taller_editor PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )

    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(taller_editor)
    endif()

    
    set_project_warnings(taller_editor ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    
    target_include_directories(taller_editor PRIVATE ${libSDL2pp_SOURCE_DIR})
endif()


# Testing section
# ---------------

if(TALLER_TESTS)
    # Let's use google test
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    # (borrowed from https://google.github.io/googletest/quickstart-cmake.html)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)

    # target for testing
    # HEY!! TODO XXX: Change the name of the executable to the one you like!
    add_executable(taller_tests)

    # HEY!! TODO XXX: I'm assuming that the code under testing is in taller_common
    # Change this if you have to.
    add_dependencies(taller_tests taller_common)

    # Say where to find the xoz headers
    # HEY!! TODO XXX: add more subfolders here
    target_include_directories(taller_tests PUBLIC .)

    # Add the source files to the taller_tests target
    # HEY!! TODO XXX: add more subfolders here
    add_subdirectory(tests/)

    # Set the compiler warnings to the tests target (but be a little lesser strict)
    set_project_warnings(taller_tests ${TALLER_MAKE_WARNINGS_AS_ERRORS} TRUE)

    # Say where googletest headers can be found
    target_include_directories(taller_tests
        PUBLIC
        ${gtest_SOURCE_DIR}/include
        ${gmock_SOURCE_DIR}/include
        )

    # HEY!! TODO XXX: I'm assuming that the code under testing is in taller_common
    # Change this if you have to.
    target_link_libraries(taller_tests
        taller_common
        GTest::gtest_main
    )
endif()
