cmake_minimum_required(VERSION 3.16)

project(CustomMiddlewareGP VERSION 0.1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(custom_middleware STATIC
    src/core/version.cpp
)

target_include_directories(custom_middleware
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


add_executable(middleware
    apps/middleware/main.cpp
)

target_compile_options(custom_middleware PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
target_link_libraries(middleware PRIVATE
    custom_middleware
)