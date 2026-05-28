#ifndef MOVER_H
#define MOVER_H
#include <rust/std.h>

typedef int move_res_int;

DECLARE_OPTION(move_res_int);

trait(Mover,
    Option(move_res_int) (*jump)(void* self);
    Option(move_res_int) (*move)(void* self);
)

#endif //MOVER_H
