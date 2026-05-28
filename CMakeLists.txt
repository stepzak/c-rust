cmake_minimum_required(VERSION 3.30)
project(c_rust_lib C)

set(CMAKE_C_STANDARD 23)

file(GLOB_RECURSE LIB_SOURCES "src/*.c")

add_library(c_rust_lib STATIC ${LIB_SOURCES}
        src/box.c
        include/rust/box.h
        include/rust/builtin_traits.h
        include/rust/traits.h)

target_include_directories(c_rust_lib PUBLIC
        include
)
add_subdirectory(examples)