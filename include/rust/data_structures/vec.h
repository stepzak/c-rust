#ifndef VEC_H
#define VEC_H
#include <stddef.h>
#include "../adt.h"

#define RVEC_INIT_CAP 2
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
#define RVEC_CHECK_TYPE(v, elem) _Static_assert(__builtin_types_compatible_p(typeof(elem), typeof(*(v))), "Type mismatch in vector operation")
#else
#define RVEC_CHECK_TYPE(v, elem) (void)elem
#endif


typedef struct {
    size_t length;
    size_t capacity;
    void (*drop_func)(void*);
    void* (*copy_func)(const void*);
} __RVec_Header;

bool _vector_grow_impl(void** data, size_t element_size, size_t prefix);
bool _vector_reserve_impl(void** data, size_t element_size, size_t capacity, size_t prefix);
bool _vector_shrink_impl(void** data, size_t element_size);
void _vector_remove_impl(void** data, size_t element_size, size_t index, void* out);
void* vector_alloc_with_prefix(size_t prefix_size, size_t item_size, size_t initial_cap);
bool vector_push_raw(void** data, void* el, size_t el_size, size_t prefix);
void _vector_cleanup(void* self);

#define Vec(T) T* __attribute__((cleanup(_vector_cleanup))

#define _rvec_header(vec) (__Rvec_Header*)(vec) - 1
#define vec_length(vec) _rvec_header(vec)->length
#define vec_capacity(vec) _rvec_header(vec)->capacity
#define vec_empty(vec) _rvec_header(vec)->length == 0

typedef size_t vec_index_t;

DECLARE_OPTION(vec_index_t);


#define vec_reserve(v, cap) ({ vector_reserve_impl((void**)&(v), sizeof(*(v)), cap, 0); })

#define vec_from_args(type, ...) \
    ({ \
        type _tmp[] = { __VA_ARGS__ }; \
        size_t _n = sizeof(_tmp) / sizeof(_tmp[0]); \
        Vec(type) _v = NULL; \
        VecStatus _status = v_reserve(_v, _n); \
        if (_status != CVEC_SUCCESS) { \
            _v = NULL; \
        } else { \
            bool _ok = true; \
            for (size_t _i = 0; _i < _n; _i++) { \
                if (v_push(_v, _tmp[_i]) != CVEC_SUCCESS) { \
                    v_free(_v); \
                    _ok = false; \
                    break; \
                } \
            } \
            if (!_ok) _v = NULL; \
        } \
        _v; \
    })

#define v_with_cap(type, cap) \
    ({ \
        Vec(type) _v = NULL; \
        VecStatus _status = v_reserve(_v, (cap)); \
        (_status == CVEC_SUCCESS) ? _v : NULL; \
    })

#define v_free(v) \
    do { \
        if (v) { \
            free(v_header(v)); \
            (v) = NULL; \
        } \
    } while(0)

#define v_push(v, elem) \
    ({ \
        VEC_CHECK_TYPE(v, elem); \
        VecStatus _status = CVEC_SUCCESS; \
        if (v_len(v) >= v_cap(v)) { \
            _status = vector_grow_impl((void**)&(v), sizeof(*(v)), 0); \
        } \
        if (_status == CVEC_SUCCESS) (v)[v_header(v)->length++] = (elem); \
        \
        _status; \
    })

#define v_pop(v) \
    do { \
        if (v_len(v) > 0) { \
            v_header(v)->length--; \
        } \
    } while (0)

#define v_free_with_dtor(v, dtor_func) \
    do { \
        if (v) { \
            for (size_t _i = 0; _i < v_len(v); _i++) { \
                dtor_func(&(v)[_i]); \
            } \
            v_free(v); \
        } \
    } while (0)

#define v_at(v, i) \
    (*({ \
        assert((v) != NULL && "Vector is NULL"); \
        size_t _i = (i); \
        assert(_i < v_header(v)->length && "Out of bounds"); \
        &(v)[_i]; \
    }))

#define v_foreach(T, item, v) \
    for (T *item = (v), *_end = (v) + v_len(v); item < _end; item++)

#define v_shrink(v) ({ vector_shrink_impl((void**)&(v), sizeof(*(v))); })

#define v_remove(v, i) vector_remove_impl((void**)&(v), sizeof(*(v)), (i))

#define v_remove_with_dtor(v, i, dtor) \
    do { \
        size_t _i = i; \
        assert(_i < v_len(v) && "Index out of range"); \
        dtor(&(v)[(_i)]); \
        vector_remove_impl((void**) &(v), sizeof(*(v)), (_i)); \
    } while (0)

#endif //VEC_H
