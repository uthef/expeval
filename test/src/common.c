#include "common.h"
#include "stdio.h"
#include "assert.h"
#include "math.h"

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

double absd(double x) {
    char* ptr = (char*)&x;
    *(ptr + (sizeof(double) - 1)) = *(ptr + (sizeof(double) - 1)) & 0x7f;
    return x;
}

double pow2(double x) {
    return pow(x, 2);
}

double modulo(double a, double b) {
    return (int)a % (int)b;
}
