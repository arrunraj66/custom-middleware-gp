include(FetchContent)

# Build only the ZeroMQ libraries required by this project.
set(BUILD_SHARED OFF CACHE BOOL "Disable shared libzmq" FORCE)
set(BUILD_STATIC ON CACHE BOOL "Build static libzmq" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "Disable libzmq tests" FORCE)
set(ENABLE_DRAFTS OFF CACHE BOOL "Disable draft ZeroMQ APIs" FORCE)
set(WITH_LIBSODIUM OFF CACHE BOOL "Disable external libsodium dependency" FORCE)

FetchContent_Declare(
    libzmq
    GIT_REPOSITORY https://github.com/zeromq/libzmq.git
    GIT_TAG v4.3.5
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(libzmq)

# cppzmq provides the C++ API in zmq.hpp.
set(CPPZMQ_BUILD_TESTS OFF CACHE BOOL "Disable cppzmq tests" FORCE)

FetchContent_Declare(
    cppzmq
    GIT_REPOSITORY https://github.com/zeromq/cppzmq.git
    GIT_TAG v4.11.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(cppzmq)

# Build Protobuf and protoc as part of this project.
set(protobuf_BUILD_TESTS OFF CACHE BOOL "Disable Protobuf tests" FORCE)
set(protobuf_BUILD_CONFORMANCE OFF CACHE BOOL "Disable conformance tests" FORCE)
set(protobuf_BUILD_EXAMPLES OFF CACHE BOOL "Disable Protobuf examples" FORCE)
set(protobuf_INSTALL OFF CACHE BOOL "Disable Protobuf installation" FORCE)
set(protobuf_BUILD_SHARED_LIBS OFF CACHE BOOL "Build static Protobuf" FORCE)
set(protobuf_WITH_ZLIB OFF CACHE BOOL "Avoid external zlib dependency" FORCE)

FetchContent_Declare(
    protobuf
    GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
    GIT_TAG v25.9
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(protobuf)

# Stable project-owned dependency targets.
add_library(custom_middleware_zeromq INTERFACE)
target_link_libraries(custom_middleware_zeromq
    INTERFACE
        cppzmq-static
)
add_library(custom_middleware::zeromq ALIAS custom_middleware_zeromq)

add_library(custom_middleware_protobuf INTERFACE)
target_link_libraries(custom_middleware_protobuf
    INTERFACE
        protobuf::libprotobuf
)
add_library(custom_middleware::protobuf ALIAS custom_middleware_protobuf)
