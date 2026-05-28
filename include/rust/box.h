#ifndef BOX_H
#define BOX_H

#include "traits.h"
#include "builtin_traits.h"
#include <stddef.h>

typedef struct {
    void (*drop_func)(void* data);
} Box_Header;

void _box_cleanup(void* ptr_to_box);
void* _box_alloc(size_t size, void (*drop_func)(void* data));

#define _box_header(box) ((Box_Header*) (box) - 1)
#define _get_drop_fn(T) \
    ({ \
        extern DropVTable T##_Drop_vtable __attribute__((weak)); \
        (&T##_Drop_vtable != NULL) ? T##_Drop_vtable.drop : NULL; \
    })

#define Box(T) T* __attribute__((cleanup(_box_cleanup)))

#define box_new(T, data) ({ \
    void (*__computed_drop)(void*) = (void(*)(void*))_get_drop_fn(T); \
    T* __p = (T*) _box_alloc(sizeof(T), __computed_drop); \
    if( __p) *__p = (data); \
    __p; \
})

extern_trait(Drop, Box);
extern_trait(Clone, Box);

#endif //BOX_H
