cmake_minimum_required(VERSION 3.13)

if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

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

# Agregar directorios
add_subdirectory(src/common)

if (TALLER_CLIENT)
    add_subdirectory(src/client)
endif()

if (TALLER_SERVER)
    add_subdirectory(src/server)
endif()

if(TALLER_EDITOR)
    add_subdirectory(src/editor)
endif()

if(TALLER_TESTS)
    add_subdirectory(tests)
endif()
