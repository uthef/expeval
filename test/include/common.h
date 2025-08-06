#define TEST_VALID_EXP(exp) test_valid_expression(#exp, exp, NULL)
#define TEST_VALID_EXP_CTX(exp, ctx) test_valid_expression(#exp, exp, ctx)
#define TEST_INVALID_EXP_CTX(exp, ctx) test_invalid_expression(#exp, exp, ctx)

#define DEFAULT_FUNCTION_SET { { "abs", absd }, { "sin", sin }, { "pow2", pow2 }, { "sqrt", sqrt }, \
    EXPEVAL_FUNCTION_TERMINATOR }

#define DEFAULT_CONSTANT_SET { { "one", 1 }, { "two", 2 }, { "three", 3 }, { "f_o_u_r", 4 }, \
    EXPEVAL_CONSTANT_TERMINATOR }
    
#define DEFAULT_OPERATOR_SET { { "%", EXPEVAL_HIGH_PRIORITY_DEFAULT + 1, modulo }, { "^", EXPEVAL_MAX_PRIORITY, pow }, \
    { "###", 0, atan2 }, EXPEVAL_OPERATOR_TERMINATOR }

#ifndef COMMON_H
#define COMMON_H

#include "expeval.h"

void test_valid_expression(const char* exp, double expected_value, expeval_context* ctx);
void test_invalid_expression(const char* exp, expeval_result_code expected_code, expeval_context* ctx);
double absd(double);
double pow2(double);
double modulo(double, double);

#endif
