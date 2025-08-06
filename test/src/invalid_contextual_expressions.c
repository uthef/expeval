#include "common.h"
#include "math.h"

int main(int argc, char** argv) {
    expeval_function functions[] = DEFAULT_FUNCTION_SET;
    expeval_constant constants[] = DEFAULT_CONSTANT_SET;
    expeval_operator operators[] = DEFAULT_OPERATOR_SET;

    expeval_context ctx;
    ctx.functions = functions;
    ctx.constants = constants;
    ctx.operators = operators;

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
