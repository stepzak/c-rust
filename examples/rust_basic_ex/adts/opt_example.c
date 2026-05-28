#include <stdio.h>

#include <rust/std.h>
#include "../examples.h"

typedef int opt_test_int;

DECLARE_OPTION(opt_test_int);

Option(opt_test_int) Step1(void) { return (Option(opt_test_int)) Some(10); }
Option(opt_test_int) Step2_Fail(void) { return (Option(opt_test_int)) None; }

Option(opt_test_int) Calculate(bool crash) {
    int a = quest_opt(Step1());
    
    int b = quest_opt(crash ? Step2_Fail() : Step1());

    return  (Option(opt_test_int)) Some(a + b);
}

void test_opt() {
        opt_test_int val;
        if (letsome(&val, Calculate(false))) {
            printf("Result: %d\n", val);
        } else {
            printf("Unexpected error\n");
        }

        if(letsome(&val, Calculate(true))) {
            printf("Success(?): %d\n", val);
        } else {
            printf("Operator ? successfull test\n");
        }

    }
