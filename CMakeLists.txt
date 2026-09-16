cmake_minimum_required(VERSION 3.16)

project(
    CustomMiddlewareGP
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

add_subdirectory(src)
add_subdirectory(apps)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
