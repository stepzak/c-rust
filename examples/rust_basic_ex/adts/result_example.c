#include <rust/std.h>
#include <stdio.h>
#include "../examples.h"

typedef char* result_example_char_ptr;

DECLARE_RESULT(int, result_example_char_ptr);

Result(int, result_example_char_ptr) parse_number(char* str) {
    if (str == NULL) return  (Result(int, result_example_char_ptr)) Err("Empty string");
    if (str[0] < '0' || str[0] > '9') return (Result(int, result_example_char_ptr)) Err("Invalid number");
    return (Result(int, result_example_char_ptr)) Ok(str[0] - '0');
}

Result(int, result_example_char_ptr) double_and_sum(char* str1, char* str2) {
    int num1 = quest_result(parse_number(str1));
    int num2 = quest_result(parse_number(str2));

    return (Result(int, result_example_char_ptr)) Ok((num1 * 2) + (num2 * 2));
}

int test_result() {
    int total;
    if(letok(&total, double_and_sum("5", "3"))) {
        printf("Result: %d\n", total);
    } else {
        printf("Unreachable\n");
    }

    Result(int, result_example_char_ptr) error_res1 = double_and_sum(NULL, "3");
    int val;
    if (letok(&val, error_res1)) {
        printf("Success(?): %d\n", val);
    } else {
        char* err = unwrap_err(error_res1);
        printf("Successful intercept: %s\n", err);
    }

    Result(int, result_example_char_ptr) error_res2 = double_and_sum("5", "abc");
    if (letok(&val, error_res2)) {
        printf("Success(?): %d\n", val);
    } else {
        char* err = unwrap_err(error_res2);
        printf("Successful intercept: %s\n", err);
    }

    return 0;
}
