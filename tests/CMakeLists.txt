function(add_middleware_test target_name source_file)
    add_executable(
        ${target_name}
        ${source_file}
    )

    target_link_libraries(
        ${target_name}
        PRIVATE
            custom_middleware
    )

    target_compile_options(
        ${target_name}
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )

    add_test(
        NAME ${target_name}
        COMMAND ${target_name}
    )
endfunction()

add_middleware_test(
    message_header_test
    message_header_test.cpp
)

add_middleware_test(
    message_test
    message_test.cpp
)

add_middleware_test(
    message_callback_test
    message_callback_test.cpp
)
