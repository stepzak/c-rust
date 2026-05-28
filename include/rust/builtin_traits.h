#ifndef BUILTIN_TRAITS_H
#define BUILTIN_TRAITS_H

#include "std.h"

trait(Drop,
    void (*drop)(void* self);
)

trait(Clone,
    void* (*clone)(const void* self);
);

#endif //BUILTIN_TRAITS_H
