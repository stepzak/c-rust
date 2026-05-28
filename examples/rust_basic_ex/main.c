#include <stdio.h>
#include "examples.h"


int main(void) {
    printf("Testing Option...\n");
    test_opt();
    printf("\nTesting Traits...\n");
    test_traits();
    printf("\nTesting Result...\n");
    test_result();
    printf("\nTesting struct impl...\n");
    test_struct_impl();
    printf("\nTesting Box...\n");
    test_box();
}