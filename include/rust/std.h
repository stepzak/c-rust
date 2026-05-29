#ifndef RUST_H
#define RUST_H

#include <assert.h>
#include <stddef.h>
#include "box.h"
#include "traits.h"
#include "builtin_traits.h"
#include "adt.h"
#include "keywords.h"

#define DECLARE_C_RUST_TYPE(T) \
    __attribute__((weak)) void __drop_fn_glue_##T(T* ptr) { \
        void (*__drop) (void*) = _get_drop_fn(T); \
        if (__drop) __drop(ptr); \
    }

#endif //RUST_H
