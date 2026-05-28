#include <stdio.h>
#include <rust/std.h>
#include "../structs/person.h"

void test_box_simple(int value) {

    Box(int) box_int = box_new(int, value);
    *box_int = value + 1;
    printf("Box value ((%d) + 1) = %d\n", value, *box_int);
}

void test_box_person(char name[20], int jump_height, int move_speed) {
    Result(Person, PERSON_NEW_ERROR) p_res = call_type_struct(Person, new, name, jump_height, move_speed);
    Person p = unwrap(p_res);
    Box(Person) p_box = box_new(Person, p);
    printf("Box Person values: %s %d %d\n", p_box->name, p_box->jump_height, p_box->move_speed);
    printf("Box Person have to be values: %s %d %d\n", name, jump_height, move_speed);
    printf("Testing box clone\n");
    TraitObject(Clone) clone_trait_box = get_trait_object(p_box, Box, Clone);
    Box(Person) cloned_box = clone_trait_box.vtable->clone(p_box);
    printf("Cloned Box values: %s %d %d\n", cloned_box->name, p_box->jump_height, p_box->move_speed);
    printf("Boxes(with person) must now be dropped via RAII\n");
}

void test_box() {
    test_box_simple(1);
    test_box_person("Artem Loh", 5, 10);
}
