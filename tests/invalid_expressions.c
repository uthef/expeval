#include "expeval.h"
#include "stdio.h"
#include "assert.h"
#include "common.h"

int main(int argc, char** argv) {
    test_invalid_expression(
        "342742378943297832489723947809234807493782438927349280794837298473243278", 
        EXPEVAL_NUMBER_TOO_BIG,
        NULL
    );

    test_invalid_expression("0..+.2", EXPEVAL_INVALID_NUMBER, NULL);
    test_invalid_expression("5,,00", EXPEVAL_INVALID_NUMBER, NULL);
    test_invalid_expression("100,+11", EXPEVAL_INVALID_NUMBER, NULL);
    test_invalid_expression("55.123.1", EXPEVAL_INVALID_NUMBER, NULL);
    test_invalid_expression("5+1+", EXPEVAL_HANGING_OPERATOR, NULL);
    test_invalid_expression("238!02", EXPEVAL_INVALID_CHAR, NULL);
    test_invalid_expression("238 # 02", EXPEVAL_INVALID_CHAR, NULL);
    test_invalid_expression("32 + (182 + (901)", EXPEVAL_BRACKET_NOT_CLOSED, NULL);
    test_invalid_expression("3 + (129-1))", EXPEVAL_UNEXPECTED_CLOSING_BRACKET, NULL);
    test_invalid_expression("-+/*", EXPEVAL_VALUE_EXPECTED, NULL);
    test_invalid_expression("12 443 92 02", EXPEVAL_OPERATOR_EXPECTED, NULL);
    test_invalid_expression("32+:", EXPEVAL_INVALID_CHAR, NULL);
    test_invalid_expression("--", EXPEVAL_VALUE_EXPECTED, NULL);
    test_invalid_expression("1*2**", EXPEVAL_VALUE_EXPECTED, NULL);
    test_invalid_expression("3-1-", EXPEVAL_HANGING_OPERATOR, NULL);
    test_invalid_expression("5e+e1", EXPEVAL_INVALID_NUMBER, NULL);
    test_invalid_expression("5e+-0", EXPEVAL_INVALID_NUMBER, NULL);
    test_invalid_expression("5e", EXPEVAL_INVALID_NUMBER, NULL);
    test_invalid_expression("5-,", EXPEVAL_INVALID_CHAR, NULL);
    test_invalid_expression("5ee", EXPEVAL_INVALID_NUMBER, NULL);
    test_invalid_expression("3 - a + b", EXPEVAL_IDENTIFIER_NOT_FOUND, NULL);
    test_invalid_expression("3 - sqrt(9) + b", EXPEVAL_IDENTIFIER_NOT_FOUND, NULL);
    test_invalid_expression("3 (231)", EXPEVAL_OPERATOR_EXPECTED, NULL);
    test_invalid_expression("(2 + 31) (761 - 1)", EXPEVAL_OPERATOR_EXPECTED, NULL);
    test_invalid_expression("3 + 8 var", EXPEVAL_OPERATOR_EXPECTED, NULL);
    test_invalid_expression("34934348 + -)", EXPEVAL_UNEXPECTED_CLOSING_BRACKET, NULL);

    return 0;
}
