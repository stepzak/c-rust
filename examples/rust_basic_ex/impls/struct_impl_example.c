#include <stdio.h>

#include "../structs/person.h"
#include "../examples.h"

Result(Person, PERSON_NEW_ERROR) test_struct_impl_new(bool should_crash ) {
    int move_speed = should_crash ? -1 : 10;
    Result(Person, PERSON_NEW_ERROR) p_res = call_type_struct(Person, new, "Se Ze", 20, move_speed);
    Person p = quest_result(p_res);
    return (Result(Person, PERSON_NEW_ERROR)) Ok(p);
}

void test_struct_impl() {
    Result(Person, PERSON_NEW_ERROR) p_res_crash = test_struct_impl_new(true);
    Person p;
    if (letok(&p, p_res_crash)) {
        printf("Invalid person test failure\n");
    } else {
        PERSON_NEW_ERROR err = unwrap_err(p_res_crash);
        if (err == PERSON_NEW_INVALID_MOVE_SPEED) printf("Invalid person test success\n");
        else printf("Invalid person test failure(invalid error)\n");
    }

    Result(Person, PERSON_NEW_ERROR) p_res_ok = test_struct_impl_new(false);
    if (letok(&p, p_res_ok)) {
        call_self_struct(&p, Person, rename, "Artem");
        printf("New person name: %s\n", p.name);
    }
}