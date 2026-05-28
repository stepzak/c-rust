#include <stdlib.h>
#include <string.h>
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

void* _box_alloc(size_t size, void (*drop_func)(void* data), void* (*clone_func)(const void* data)) {
    Box_Header* h = malloc(size + sizeof(Box_Header));
    if (h == NULL) return NULL;
    h->drop_func = drop_func;
    h->data_size = size;
    h->clone_func = clone_func;
    void* d = h + 1;
    return d;
}

void Box_drop(void* self) {
    if (!self) return;
    Box_Header* h = _box_header(self);
    if (h->drop_func) {
        h->drop_func(self);
    }
    free(h);
}

void* Box_clone(const void* data) {
    if (!data) return NULL;
    Box_Header* h = _box_header(data);
    Box_Header* new_h = malloc(sizeof(Box_Header) + h->data_size);
    if (new_h == NULL) return NULL;
    new_h->drop_func = h->drop_func;
    new_h->data_size = h->data_size;
    new_h->clone_func = h->clone_func;
    void* d = new_h + 1;
    if (h->clone_func) {
        void* cloned = h->clone_func(data);
        if (!cloned) {
            free(new_h);
            return NULL;
        }
        memcpy(d, cloned, h->data_size);
        free(cloned);
    } else {
        memcpy(d, data, new_h->data_size);
    }
    return d;
}

impl_trait(Drop, Box, .drop = Box_drop)
impl_trait(Clone, Box, .clone = Box_clone)