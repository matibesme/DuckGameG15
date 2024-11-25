# Configuración de la biblioteca común
add_library(taller_common STATIC)

# Archivos fuente de la biblioteca común
file(GLOB_RECURSE COMMON_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)
target_sources(taller_common PRIVATE ${COMMON_SOURCES})

# Incluir directorios de encabezados
target_include_directories(taller_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Configurar advertencias
include(${CMAKE_SOURCE_DIR}/cmake/CompilerWarnings.cmake)
set_project_warnings(taller_common TRUE FALSE)
