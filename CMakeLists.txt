cmake_minimum_required(VERSION 3.16)

project(
    CustomMiddlewareGP
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create the middleware static library.
add_library(custom_middleware STATIC
    src/core/version.cpp
)

# Make the include directory available to the library
# and every executable that links to it.
target_include_directories(custom_middleware
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(custom_middleware
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

# Main middleware executable.
add_executable(middleware
    apps/middleware/main.cpp
)

target_link_libraries(middleware
    PRIVATE
        custom_middleware
)

target_compile_options(middleware
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

# Enable CTest.
enable_testing()

# MessageHeader test.
add_executable(message_header_test
    tests/message_header_test.cpp
)

target_link_libraries(message_header_test
    PRIVATE
        custom_middleware
)

target_compile_options(message_header_test
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

add_test(
    NAME message_header_test
    COMMAND message_header_test
)

# Complete Message test.
add_executable(message_test
    tests/message_test.cpp
)

target_link_libraries(message_test
    PRIVATE
        custom_middleware
)

target_compile_options(message_test
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

add_test(
    NAME message_test
    COMMAND message_test
)