#include <stdlib.h>
#include <rust/box.h>

void _box_cleanup(void* ptr_to_box) {
    void** ptr = (void**)ptr_to_box;
    if (!*ptr) return;
    void* box = *ptr;
    Box_Header* h = _box_header(box);
    if (h->drop_func) {
        h->drop_func(box);
    }
    free(h);
    *ptr = NULL;
}

void* _box_alloc(size_t size, void (*drop_func)(void* data) ) {
    Box_Header* h = malloc(size + sizeof(Box_Header));
    if (h == NULL) return NULL;
    h->drop_func = drop_func;
    void* d = h + 1;
    return d;
}

void Box_drop(void* self) {
    _box_cleanup(&self);
}

impl_trait(Drop, Box, .drop = Box_drop)