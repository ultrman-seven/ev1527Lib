cmake_minimum_required(VERSION 3.20)

project(Ev1527Decode)
add_library(Ev1527Decode INTERFACE)

enable_language(C)

target_compile_definitions(Ev1527Decode INTERFACE
)

target_include_directories(Ev1527Decode INTERFACE
    ./
    )

target_sources(Ev1527Decode INTERFACE
    ./ev1527decode.c
)

target_link_directories(tek INTERFACE
)

target_link_libraries(tek INTERFACE
)
