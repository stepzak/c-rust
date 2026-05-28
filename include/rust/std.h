#ifndef RUST_H
#define RUST_H

#include <assert.h>
#include <stddef.h>
#include "box.h"
#include "traits.h"

#define DECLARE_RESULT(T, E) \
    struct __Result_ ## T ## _ ## E { \
        bool ok; \
        union { T res; E err; }; \
    }

#define Result(T, E) struct __Result_ ## T ## _ ## E

#define Ok(val) { .ok = true, .res = (val) }
#define Err(val) { .ok = false, .err = (val) }

#define is_ok(val) ((val).ok)
#define is_err(val) (!(val).ok)

#define unwrap(val) ({ \
    typeof(val) _val = (val); \
    assert(_val.ok && "panic: Tried to unwrap an error!"); \
    _val.res; \
})

#define unwrap_err(val) ({ \
    typeof(val) _val = (val); \
    assert(!_val.ok && "panic: Tried to unwrap error but value was OK"); \
    _val.err; \
})

#define letok(var_ptr, res) ({ \
    bool _letok_res = false; \
    typeof(res) _res = (res); \
    if (is_ok(_res)) { \
        *(var_ptr) = unwrap(_res); \
        _letok_res = true; \
    } \
    _letok_res; \
})

#define leterr(err_ptr, res) ({ \
    bool _leterr_res = false; \
    typeof(res) _res = (res); \
    if (is_err(_res)) { \
        *(err_ptr) = unwrap_err(_res); \
        _leterr_res = true; \
    } \
    _leterr_res; \
})

#define quest_result(result) ({ \
    typeof(result) _quest_res_val = (result); \
    typeof(_quest_res_val.res) __quest_res_res; \
    if (!letok(&__quest_res_res, _quest_res_val)) { \
        return (typeof(result)) { \
            .ok = false, \
            .err = unwrap_err(_quest_res_val) \
        }; \
    } \
    __quest_res_res; \
})


#define DECLARE_OPTION(T) \
    struct __Option_ ## T { \
        bool has_value; \
        T value; \
    }

#define Option(T) struct __Option_ ## T

#define Some(val) { .has_value = true, .value = (val) }
#define None { .has_value = false }

#define is_some(val) ((val).has_value)
#define is_none(val) (!(val).has_value)

#define unwrap_opt(val) ({ \
    typeof(val) _val = (val); \
    assert(_val.has_value && "panic: Tried to unwrap None!"); \
    _val.value; \
})

#define letsome(var_ptr, opt) ({ \
    bool _letsome_res = false; \
    typeof(opt) _opt = (opt); \
    if (is_some(_opt)) { \
        *(var_ptr) = unwrap_opt(_opt); \
        _letsome_res = true; \
    } \
    _letsome_res; \
})

#define quest_opt(opt) ({ \
    typeof(opt) _quest_opt_val = (opt); \
    typeof(_quest_opt_val.value) __quest_opt_res; \
    if (!letsome(&__quest_opt_res, _quest_opt_val)) { \
        return (typeof(opt)) { .has_value = false }; \
    } \
    __quest_opt_res; \
})


#endif //RUST_H
