#ifndef TRAITS_H
#define TRAITS_H

#define trait(TraitName, ...) \
    typedef struct TraitName##VTable { \
        __VA_ARGS__ \
    } TraitName##VTable; \
    typedef struct TraitName##Object { \
        void* data; \
        TraitName##VTable* vtable; \
    } TraitName##Object;

#define impl_trait(TraitName, StructName, ...) \
    TraitName##VTable StructName##_##TraitName##_vtable = { __VA_ARGS__ };

#define TraitObject(TraitName) TraitName##Object

#define get_trait_object(stct, StructName, TraitName) ({ \
    TraitObject(TraitName) __trait_obj; \
    __trait_obj.vtable = &StructName##_##TraitName##_vtable; \
    __trait_obj.data = (void*)&(stct); \
    __trait_obj; \
})

#define traits_combo(TraitName, Trait1Name, Trait2Name) \
    typedef struct TraitName##VTable { \
        Trait1Name##VTable* Trait1Name; \
        Trait2Name##VTable* Trait2Name; \
    } TraitName##VTable; \
    typedef struct TraitName##Object { \
        void* data; \
        TraitName##VTable* vtable; \
    } TraitName##Object;

#define impl_traits_combo(TraitName, StructName, Trait1Name, Trait2Name) \
    TraitName##VTable StructName##_##TraitName##_vtable = { \
        .Trait1Name = &StructName##_##Trait1Name##_vtable, \
        .Trait2Name = &StructName##_##Trait2Name##_vtable  \
    };

#define extern_trait(TraitName, StructName) extern TraitName##VTable StructName##_##TraitName##_vtable;

#define define_struct_methods(StructName, ...) \
    typedef struct StructName##_StructVTable { __VA_ARGS__ } StructName##_StructVTable; \
    typedef struct StructName##_StructObjectVtable { void* data; StructName##_StructVTable* vtable; } StructName##_StructObjectVtable; \
    extern StructName##_StructVTable StructName##_Struct_impl;

#define impl_struct(StructName, ...) \
    StructName##_StructVTable StructName##_Struct_impl = { __VA_ARGS__ } ;

#define StructVtableObject(StructName) StructName##_StructObjectVtable

#define get_struct_vtable_obj(self, StructName) ({ \
      StructVtableObject(StructName) __struct_vtable_res; \
     __struct_vtable_res.data = (void*) (self); \
     __struct_vtable_res.vtable = &StructName##_Struct_impl; \
     __struct_vtable_res; \
})

#define call_self_struct(self, StructName, method, ...) ({ \
    typeof(self) __call_self_self = (self); \
    StructVtableObject(StructName) __call_self_struct_struct_vtable = get_struct_vtable_obj(__call_self_self, StructName); \
     __call_self_struct_struct_vtable.vtable->method(__call_self_struct_struct_vtable.data, ##__VA_ARGS__); \
})

#define call_type_struct(StructName, method, ...) ({ \
    ( get_struct_vtable_obj(NULL, StructName) ).vtable->method(__VA_ARGS__); \
})
#endif //TRAITS_H
