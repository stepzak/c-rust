#ifndef PERSON_H
#define PERSON_H

#include <rust/std.h>
#include "../traits_def/speaker.h"
#include "../traits_def/mover.h"
#include "../traits_def/mover_x_speaker.h"

typedef enum {
    PERSON_NEW_INVALID_JUMP_HEIGHT,
    PERSON_NEW_INVALID_MOVE_SPEED,
} PERSON_NEW_ERROR;



typedef struct Person Person;

struct Person {
    char name[20];
    int jump_height;
    int move_speed;
};

DECLARE_RESULT(Person, PERSON_NEW_ERROR);

extern_trait(Speaker, Person)
extern_trait(Mover, Person)
extern_trait(MoverXSpeaker, Person)

define_struct_methods(Person,
    Result(Person, PERSON_NEW_ERROR) (*new)(char name[20], int jump_height, int move_speed);
    void (*rename)(Person* self, char new_name[20]);
)

#endif //PERSON_H
