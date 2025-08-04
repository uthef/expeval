#include "common.h"
#include "stdio.h"
#include "assert.h"

void test_valid_expression(const char* exp, double expected_value, expeval_context* ctx) {
    expeval_result result = expeval(exp, ctx);
    
    printf("Expression: %s\n", exp);
    printf("Code: %s\n", expeval_result_code_as_str(result.code));

    if (result.code != EXPEVAL_OK) {
        printf("Error position: %zu\n", result.err_pos);
    }

    printf("Result: %lf\n", result.value);
    printf("Expected result: %lf\n", expected_value);

    assert(result.code == EXPEVAL_OK);
    assert(result.value == expected_value);
    printf("\n");
}

void test_invalid_expression(const char* exp, expeval_result_code expected_code, expeval_context* ctx) {
    expeval_result result = expeval(exp, ctx);
    
    printf("Expression: %s\n", exp);
    printf("Code: %s\n", expeval_result_code_as_str(result.code));
    printf("Position: %zu\n", result.err_pos);

    assert(result.code == expected_code);

    printf("\n");
}
