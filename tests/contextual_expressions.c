#include "expeval.h"
#include "common.h"
#include "math.h"
#include "stdlib.h"

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

int main(int argc, char** argv) {
    expeval_function functions[] = {
        { "abs", absd }, 
        { "sin", sin },
        { "pow2", pow2 },
        { "sqrt", sqrt },
        EXPEVAL_FUNCTION_TERMINATOR
    };

    expeval_constant constants[] = {
        { "one", 1 },
        { "two", 2 },
        { "three", 3 },
        { "f_o_u_r", 4 },
        EXPEVAL_CONSTANT_TERMINATOR
    };

    expeval_operator operators[] = {
        { "%", EXPEVAL_HIGH_PRIORITY_DEFAULT + 1, modulo },
        { "^", EXPEVAL_MAX_PRIORITY, pow },
        { "###", 0, atan2 },
        EXPEVAL_OPERATOR_TERMINATOR
    };

    expeval_context ctx;
    ctx.functions = functions;
    ctx.constants = constants;
    ctx.operators = operators;

    test_valid_expression("sqrt(49) - abs(-7) + two * 2", sqrt(49) - abs(-7) + 2 * 2, &ctx);
    test_valid_expression("one+two+three * f_o_u_r", 1 + 2 + 3 * 4, &ctx); 
    test_valid_expression("-sqrt(144) * sqrt(144)", -sqrt(144) * sqrt(144), &ctx);
    test_valid_expression("- two + -(one)", -2 + -(1), &ctx);
    test_valid_expression("one-(53)", 1 - 53, &ctx);
    test_valid_expression("abs(f_o_u_r * 2/2)", abs(4 * 2 / 2), &ctx);
    test_valid_expression("-3 + -sin(4) * (200 - 10 ^ 2)", -3 + -sin(4) * (200 - pow(10, 2)), &ctx);
    test_valid_expression("-two - -sqrt(4) + 12", -2 - -sqrt(4) + 12, &ctx);
    test_valid_expression("100. / 24 % 22", 100. / (24 % 22), &ctx);
    test_valid_expression(".5+39%(21)%f_o_u_r/24+11", .5 + (39 % (21) % 4) / 24. + 11., &ctx);
    test_valid_expression("30 % 16", 30 % 16, &ctx);
    test_valid_expression("293%29%11", 293 % 29 % 11, &ctx);
    test_valid_expression("219 % 32 / 6 % 18 - 14 * 21 % 7", (219 % 32) / (double)(6 % 18) - 14 * (21 % 7), &ctx);
    test_valid_expression("2 * 3 ###two+10", atan2(2 * 3, 2 + 10), &ctx);

    test_valid_expression("10 ^ 2", pow(10, 2), &ctx);
    test_valid_expression("10 ^ 2 ^ 3", pow(pow(10, 2), 3), &ctx);
    test_valid_expression("686 / 7 ^ 3 - 11", 686 / pow(7, 3) - 11, &ctx);
    test_valid_expression(
        "4 ^ 2 - 1 / 5 / 2 + 1 * 3 + 2 ^ 2 / 2", 
        pow(4, 2) - 1.0 / 5.0 / 2.0 + 1.0 * 3.0 + pow(2, 2) / 2.0,
        &ctx
    );
    test_valid_expression("4 ^ 2 / 1.5 * 5", pow(4, 2) / 1.5 * 5.0, &ctx);
    test_valid_expression(
        "((.0 - 14 * 2.00) + (12 - 2. / 2) + (-4 + 8)^2.)", 
        ((.0 - 14 * 2) + (12 - 2. / 2) + pow((-4 + 8), 2)),
        &ctx
    );
    
    TEST_VALID_EXP_CTX(6 + 1 * 298 + sqrt(81) + 16.0 / 24., &ctx);
    TEST_VALID_EXP_CTX(pow2(2+2)+2, &ctx);

    test_invalid_expression("3##16", EXPEVAL_INVALID_CHAR, &ctx);
    test_invalid_expression("3####16", EXPEVAL_INVALID_CHAR, &ctx);
    test_invalid_expression("sqrt (64)", EXPEVAL_IDENTIFIER_NOT_FOUND, &ctx);
    test_invalid_expression("absd(-64)", EXPEVAL_IDENTIFIER_NOT_FOUND, &ctx);
    test_invalid_expression("A + B", EXPEVAL_IDENTIFIER_NOT_FOUND, &ctx);
    test_invalid_expression("two one", EXPEVAL_OPERATOR_EXPECTED, &ctx);
    test_invalid_expression("two-+", EXPEVAL_VALUE_EXPECTED, &ctx);
    test_invalid_expression("abs(one) (123)", EXPEVAL_OPERATOR_EXPECTED, &ctx);
    test_invalid_expression("three 32", EXPEVAL_OPERATOR_EXPECTED, &ctx);
    test_invalid_expression("438three", EXPEVAL_OPERATOR_EXPECTED, &ctx);
    test_invalid_expression("f_o_u_r (320 / 2)", EXPEVAL_OPERATOR_EXPECTED, &ctx);
    test_invalid_expression("438sqrt(900)", EXPEVAL_OPERATOR_EXPECTED, &ctx);
    test_invalid_expression("38 + 8 - @", EXPEVAL_INVALID_CHAR, &ctx);
    test_invalid_expression("%5", EXPEVAL_VALUE_EXPECTED, &ctx);
    test_invalid_expression("5%", EXPEVAL_HANGING_OPERATOR, &ctx);
    test_invalid_expression("   %", EXPEVAL_VALUE_EXPECTED, &ctx);
    test_invalid_expression("32% ^", EXPEVAL_VALUE_EXPECTED, &ctx);
    test_invalid_expression("32%+", EXPEVAL_VALUE_EXPECTED, &ctx);

    return 0;
}
