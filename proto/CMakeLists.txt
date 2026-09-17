include(FetchContent)

FetchContent_GetProperties(protobuf)

include(
    ${protobuf_SOURCE_DIR}/cmake/protobuf-generate.cmake
)

set(
    PROTO_GENERATED_DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/generated
)
file(
    MAKE_DIRECTORY
    ${PROTO_GENERATED_DIRECTORY}
)
add_library(custom_middleware_messages STATIC
    message_envelope.proto
)

target_link_libraries(custom_middleware_messages
    PUBLIC
        custom_middleware::protobuf
)

target_include_directories(custom_middleware_messages
    SYSTEM
    PUBLIC
        ${PROTO_GENERATED_DIRECTORY}
)

protobuf_generate(
    TARGET custom_middleware_messages
    LANGUAGE cpp
    IMPORT_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${protobuf_SOURCE_DIR}/src
    PROTOC_OUT_DIR
        ${PROTO_GENERATED_DIRECTORY}
)

add_library(
    custom_middleware::messages
    ALIAS
    custom_middleware_messages
)