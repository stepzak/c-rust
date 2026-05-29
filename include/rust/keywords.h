#ifndef KEYWORDS_H
#define KEYWORDS_H


#define let(T, name) \
    T name __attribute__((cleanup(__drop_fn_glue_##T)))

#define move_out(var) ({ \
    typeof(var) __ret = (var); \
    (var) = NULL; \
    __ret; \
})

#endif //KEYWORDS_H
