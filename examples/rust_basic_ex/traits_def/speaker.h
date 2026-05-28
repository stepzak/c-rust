#ifndef SPEAK_H
#define SPEAK_H

#include <rust/std.h>

trait(Speaker,
    void (*speak)(void* self);
)

#endif //SPEAK_H
