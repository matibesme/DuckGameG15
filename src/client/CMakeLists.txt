set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(taller_client)

#find_package(Qt5 COMPONENTS Widgets REQUIRED)
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

target_include_directories(taller_client PRIVATE 
    ${CMAKE_SOURCE_DIR}/src/client 
    ${CMAKE_SOURCE_DIR}/src/common
)

add_dependencies(taller_client taller_common SDL2pp::SDL2pp)

target_link_libraries(taller_client PRIVATE 
    taller_common
    SDL2::SDL2 
    SDL2pp::SDL2pp 
    SDL2_image::SDL2_image 
    SDL2_mixer::SDL2_mixer 
    SDL2_ttf::SDL2_ttf 
    Qt5::Widgets
)

set_project_warnings(taller_client ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

