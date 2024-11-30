set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include(FetchContent)
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

add_executable(taller_client)

#find_package(SDL2_image REQUIRED)
#find_package(SDL2_mixer REQUIRED)
#find_package(SDL2_ttf REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)


file(GLOB_RECURSE CLIENT_SOURCES
        "${CMAKE_SOURCE_DIR}/src/client/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/client/*.h"
)

file(GLOB COMMON_SOURCES
        "${CMAKE_SOURCE_DIR}/src/common/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/common/*.h"
)

target_sources(taller_client PRIVATE ${CLIENT_SOURCES} ${COMMON_SOURCES})

target_include_directories(taller_client PRIVATE ${CMAKE_SOURCE_DIR}/src/client ${CMAKE_SOURCE_DIR}/src/common)
add_dependencies(taller_client taller_common SDL2pp::SDL2pp)
target_link_libraries(taller_client taller_common SDL2pp::SDL2pp SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer Qt5::Widgets SDL2_ttf::SDL2_ttf)
set_project_warnings(taller_client ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)
