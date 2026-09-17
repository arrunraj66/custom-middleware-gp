add_library(custom_middleware STATIC
    core/version.cpp
    serialization/message_serializer.cpp
)

target_include_directories(custom_middleware
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(custom_middleware
    PRIVATE
        custom_middleware::messages
)

target_compile_options(custom_middleware
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)