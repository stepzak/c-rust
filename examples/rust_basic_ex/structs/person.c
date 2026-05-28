#include "person.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void person_speak(void* self) {
    Person* p = (Person*) self;
    printf("My name is %s!\n", p->name);
}

Option(move_res_int) person_move(void* self) {
    Person* p = (Person*) self;
    printf("Person moving...\n");
    return (Option(move_res_int)) Some(p->move_speed);
}

Option(move_res_int) person_jump(void* self) {
    Person* p = (Person*) self;
    printf("Person jumping...\n");
    return (Option(move_res_int)) None;
}

Result(Person, PERSON_NEW_ERROR) Person_new(char name[20], int jump_height, int move_speed) {
    if (jump_height <= 0) return (Result(Person, PERSON_NEW_ERROR)) Err(PERSON_NEW_INVALID_JUMP_HEIGHT);
    if (move_speed <= 0) return (Result(Person, PERSON_NEW_ERROR)) Err(PERSON_NEW_INVALID_MOVE_SPEED);
    Person p;
    strncpy(p.name, name, sizeof(p.name) - 1);
    p.name[sizeof(p.name) - 1] = '\0';
    p.jump_height = jump_height;
    p.move_speed = move_speed;
    return (Result(Person, PERSON_NEW_ERROR)) Ok(p);
}

void Person_rename(Person* self, char new_name[20]) {
    strncpy(self->name, new_name, sizeof(self->name) - 1);
    self->name[sizeof(self->name) - 1] = '\0';
}

void Person_drop(void* self) {
    printf("[RAII] Person dropping...\n");
}

impl_trait(Drop, Person, .drop = Person_drop);

impl_struct(Person,
    .new = Person_new,
    .rename = Person_rename
)

impl_trait(Speaker, Person, person_speak)
impl_trait(Mover, Person, .jump = person_jump, .move = person_move)
impl_traits_combo(MoverXSpeaker, Person, Mover, Speaker)