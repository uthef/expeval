#include "expeval.h"
#include "stdio.h"
#include "assert.h"
#include "math.h"
#include "common.h"

int main(int argc, char** argv) {
    printf("%zu\n%zu\n%zu\n", sizeof(expeval_operator), sizeof(expeval_constant), sizeof(expeval_function));
    test_valid_expression("", 0, NULL);
    test_valid_expression("()", 0, NULL);
    test_valid_expression("5,000", 5000, NULL);
    test_valid_expression("2.0e0*400,000", 2.0e0 * 400000, NULL);
    test_valid_expression("1,2,3,4e+0-000,2,3,4e+0", 1234e+0 - 234e+0, NULL);
    test_valid_expression("5--5+-2", 5 - -5 + -2, NULL);

    TEST_VALID_EXP(-5 - -4 + -18 * (-11 + 4));
    TEST_VALID_EXP(2 + 2 * 2);
    TEST_VALID_EXP((80));
    TEST_VALID_EXP((80.000));
    TEST_VALID_EXP(11-(40 +40) * 2);
    TEST_VALID_EXP(100 + 200 + 300 + 400 - 5 + 5 - 5);
    TEST_VALID_EXP(17.0 / 8.0 * 13.0 * 84.0 / 3.0);
    TEST_VALID_EXP(4.0 / 2.0);
    TEST_VALID_EXP(4.0 / 2.0 * 3);
    TEST_VALID_EXP(9743.0 * 80 - 14 + 1);
    TEST_VALID_EXP(9743.0 + 1 * 80 - 14);
    TEST_VALID_EXP(13 - 9743.0 * 80 * 14);
    TEST_VALID_EXP(72 + 1 + 9);
    TEST_VALID_EXP(9000 - 800);
    TEST_VALID_EXP(-5-5);
    TEST_VALID_EXP((-5) + -(-10 + -2));

    TEST_VALID_EXP(((((10 + 4 - 12 * 5) +((5.0/2)) * ((((3*7)))) - 80 + 2 / 55.23))));
    TEST_VALID_EXP(((((800+(8+8))))-16)*2);
    TEST_VALID_EXP(2 + 2 * 5 / 4.000);
    TEST_VALID_EXP(88 - 88 * 90 + (11 / (4. * 19)));
    TEST_VALID_EXP(1234.1234 - .1234);
    TEST_VALID_EXP(-5 * (-18. / 2.) - 14 + (-140));
    TEST_VALID_EXP(((-5 + (-298 + 5 * 2) - (-100))));
    TEST_VALID_EXP(55 * 2e+1 + 4e1 * ((-0.2e+4) * .1e-1));
    TEST_VALID_EXP(55+12);
    TEST_VALID_EXP(1.4e+4+3.5e-4);
    TEST_VALID_EXP(0.005);
    TEST_VALID_EXP(12 + 8 - 16 + (-24));
    TEST_VALID_EXP(-5e-5-((-1)));
    TEST_VALID_EXP(-(-(0)));

    printf("All tests have passed!\n");

    return 0;
}
