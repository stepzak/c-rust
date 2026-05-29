cmake_minimum_required(VERSION 3.30)
project(c_rust_lib C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON)

file(GLOB_RECURSE LIB_SOURCES "src/*.c")

add_library(c_rust_lib STATIC ${LIB_SOURCES}
        src/box.c
        include/rust/box.h
        include/rust/builtin_traits.h
        include/rust/traits.h
        include/rust/data_structures/vec.h
        include/rust/adt.h
        include/rust/keywords.h
        include/rust/builtin_helpers.h
)


target_include_directories(c_rust_lib PUBLIC
        include
)
add_subdirectory(examples)