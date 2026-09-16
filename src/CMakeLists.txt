add_library(custom_middleware STATIC
    core/version.cpp
)

target_include_directories(custom_middleware
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(custom_middleware
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
