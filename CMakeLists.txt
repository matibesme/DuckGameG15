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

include(FetchContent)

# Declaración de dependencias de SDL
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.8
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    OVERRIDE_FIND_PACKAGE
)

FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.2
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    OVERRIDE_FIND_PACKAGE
)

FetchContent_Declare(
    SDL2_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG release-2.8.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    OVERRIDE_FIND_PACKAGE
)

FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.22.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    OVERRIDE_FIND_PACKAGE
)

FetchContent_Declare(
    libSDL2pp
    OVERRIDE_FIND_PACKAGE
    URL https://github.com/libSDL2pp/libSDL2pp/archive/cc198c9a5657048bee67ece82de620b2d5661084.zip
)

FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_mixer SDL2_ttf libSDL2pp)

#Verificar dependencias
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

# Opciones de compilación
option(TALLER_TESTS "Enable / disable tests." ON)
option(TALLER_CLIENT "Enable / disable client program." ON)
option(TALLER_SERVER "Enable / disable server program." ON)
option(TALLER_EDITOR "Enable / disable editor program." ON)
option(TALLER_MAKE_WARNINGS_AS_ERRORS "Enable / disable warnings as errors." ON)

message(CMAKE_CXX_COMPILER_ID="${CMAKE_CXX_COMPILER_ID}")

# Definiciones globales
add_definitions(-DDATA_PATH="/var/TallerDuckGame")
add_definitions(-DCONFIG_PATH="/etc/TallerDuckGame")

# Subdirectorios
add_subdirectory(src/common)

if (TALLER_CLIENT)
    add_subdirectory(src/client)
    install(TARGETS taller_client DESTINATION /usr/bin)
endif()

if (TALLER_SERVER)
    add_subdirectory(src/server)
    install(TARGETS taller_server DESTINATION /usr/bin)
endif()

if (TALLER_EDITOR)
    add_subdirectory(src/editor)
    install(TARGETS taller_editor DESTINATION /usr/bin)
endif()

if (TALLER_TESTS)
    add_subdirectory(tests)
endif()

# Instalación de recursos y configuraciones
install(DIRECTORY ${PROJECT_SOURCE_DIR}/data/ DESTINATION /var/TallerDuckGame FILE_PERMISSIONS WORLD_WRITE WORLD_READ WORLD_EXECUTE DIRECTORY_PERMISSIONS WORLD_WRITE WORLD_READ WORLD_EXECUTE)
install(FILES ${PROJECT_SOURCE_DIR}/data/editor/menu_config.yaml DESTINATION /etc/TallerDuckGame PERMISSIONS WORLD_WRITE WORLD_READ WORLD_EXECUTE)
install(FILES ${PROJECT_SOURCE_DIR}/src/server/configuration/config.yaml DESTINATION /etc/TallerDuckGame PERMISSIONS WORLD_WRITE WORLD_READ WORLD_EXECUTE)

