# Let's use Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Target for testing
add_executable(taller_tests)

# Assume the code under testing is in taller_common
add_dependencies(taller_tests taller_common)

# Say where to find the headers for testing and common code
target_include_directories(taller_tests PUBLIC .)

# Add the source files for client and server protocol implementations
target_sources(taller_tests PRIVATE
        ../src/client/protocolo_cliente.cpp
        ../src/server/protocolo_server.cpp
        ../src/common/protocolo.cpp
        ../src/common/socket.cpp
        ../src/common/resolver.cpp  # ¡Agregado!
        ../src/common/liberror.cpp
        ../src/common/resolvererror.cpp
        testsProtocol.cpp
)

# Include all test files in the tests folder
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp" "tests/*.h")
target_sources(taller_tests PRIVATE ${TEST_SOURCES})

# Set compiler warnings for tests (optional strictness)
set_project_warnings(taller_tests ${TALLER_MAKE_WARNINGS_AS_ERRORS} TRUE)

# Include directories for Google Test and Mock
target_include_directories(taller_tests
        PUBLIC
        ${gtest_SOURCE_DIR}/include
        ${gmock_SOURCE_DIR}/include
)

# Link the libraries (common code and Google Test/Mock)
target_link_libraries(taller_tests
        taller_common
        GTest::gtest_main
        GTest::gmock
)

# Register tests with CTest
gtest_discover_tests(taller_tests)
