add_executable(taller_server)

file(GLOB_RECURSE SERVER_SOURCES
        "${CMAKE_SOURCE_DIR}/src/server/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/server/*.h"
        "${CMAKE_SOURCE_DIR}/src/server/*.yaml"
)

file(GLOB COMMON_SOURCES
        "${CMAKE_SOURCE_DIR}/src/common/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/common/*.h"
)

target_sources(taller_server PRIVATE ${SERVER_SOURCES} ${COMMON_SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/src/server ${CMAKE_SOURCE_DIR}/src/common)
add_dependencies(taller_server taller_common)
target_link_libraries(taller_server taller_common yaml-cpp)
set_project_warnings(taller_server ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)
