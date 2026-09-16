add_executable(middleware
    main.cpp
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
