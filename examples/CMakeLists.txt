add_executable(rust_demo rust_basic_ex/main.c
        rust_basic_ex/structs/person.h
        rust_basic_ex/impls/traits_example.c
        rust_basic_ex/adts/opt_example.c
        rust_basic_ex/structs/person.c
        rust_basic_ex/adts/result_example.c
        rust_basic_ex/impls/struct_impl_example.c
        rust_basic_ex/smart_pointers/box_ex.c)
target_link_libraries(rust_demo PRIVATE c_rust_lib)