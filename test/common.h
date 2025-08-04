#define TEST_VALID_EXP(exp) test_valid_expression(#exp, exp, NULL)
#define TEST_VALID_EXP_CTX(exp, ctx) test_valid_expression(#exp, exp, ctx)
#define TEST_INVALID_EXP_CTX(exp, ctx) test_invalid_expression(#exp, exp, ctx)

#ifndef COMMON_H
#define COMMON_H

#include "expeval.h"

void test_valid_expression(const char* exp, double expected_value, expeval_context* ctx);
void test_invalid_expression(const char* exp, expeval_result_code expected_code, expeval_context* ctx);

#endif
