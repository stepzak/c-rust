#ifndef BUILTIN_TRAITS_H
#define BUILTIN_TRAITS_H

#include "traits.h"
#include <stdbool.h>

trait(Drop,
    void (*drop)(void* self);
)

trait(Clone,
    void* (*clone)(const void* self);
);

trait(Len,
    size_t (*len)(const void* self);
    bool (*is_empty)(const void* self);
);

#define _get_any_vtable_func(T, Trait, func)  \
    ({ \
        extern Trait##VTable T##_##Trait##_vtable __attribute__((weak)); \
        (&T##_##Trait##_vtable != NULL) ? T##_##Trait##_vtable.func : NULL; \
    })

#endif //BUILTIN_TRAITS_H
