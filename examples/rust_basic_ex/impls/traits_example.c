#include <stdio.h>
#include <rust/std.h>
#include "../structs/person.h"
#include "../examples.h"

void dispatcher(TraitObject(MoverXSpeaker) smbd) {
    printf("Dispatcher\n");
    smbd.vtable->Speaker->speak(smbd.data);
    Option(move_res_int) jump_opt = smbd.vtable->Mover->jump(smbd.data);
    move_res_int jump_i;
    if (letsome(&jump_i, jump_opt)) {
        printf("jump_i: %d\n", jump_i);
    } else {
        printf("jump_i is None\n");
    }
    Option(move_res_int) move_res = smbd.vtable->Mover->move(smbd.data);
    move_res_int move_i;
    if (letsome(&move_i, move_res)) {
        printf("move_i: %d\n", move_i);
    } else {
        printf("move_i is None\n");
    }
}

void test_traits() {
    Person person = {.name ="Artem Loh", 10, 15};
    TraitObject(MoverXSpeaker) smbd = get_trait_object(person, Person, MoverXSpeaker);
    dispatcher(smbd);
}