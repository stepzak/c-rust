#ifndef BOX_H
#define BOX_H

#include "traits.h"
#include "builtin_traits.h"
#include <stddef.h>

typedef struct Box_Header {
    void (*drop_func)(void* data);
    void* (*clone_func)(const void* data);
    size_t data_size;
} Box_Header;

void _box_cleanup(void* ptr_to_box);
void* _box_alloc(size_t size, void (*drop_func)(void* data), void* (*clone_func)(const void* data));

#define _box_header(box) ((Box_Header*) (box) - 1)

#define Box(T) T* __attribute__((cleanup(_box_cleanup)))

#define box_new(T, data) ({ \
    void (*__computed_drop)(void*) = (void(*)(void*))_get_drop_fn(T); \
    void* (*__computed_clone) (const void*) = (void* (*)(const void*)) _get_clone_fn(T); \
    T* __p = (T*) _box_alloc(sizeof(T), __computed_drop, __computed_clone); \
    if( __p) *__p = (data); \
    __p; \
})

extern_trait(Drop, Box);
extern_trait(Clone, Box);

#endif //BOX_H
