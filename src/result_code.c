#include "result_code.h"

#define STR(x) #x

const char* expeval_result_code_as_str(expeval_result_code code) {
    switch (code) {
        case EXPEVAL_OK:
            return STR(EXPEVAL_OK);
        case EXPEVAL_INVALID_CHAR:
            return STR(EXPEVAL_INVALID_CHAR);
        case EXPEVAL_NUMBER_TOO_BIG:
            return STR(EXPEVAL_NUMBER_TOO_BIG);
        case EXPEVAL_INVALID_NUMBER:
            return STR(EXPEVAL_INVALID_NUMBER);
        case EXPEVAL_MEMORY_ALLOCATION_IMPOSSIBLE:
            return STR(EXPEVAL_MEMORY_ALLOCATION_IMPOSSIBLE);
        case EVPEVAL_EXPECTED_OPENING_BRACKET:
            return STR(EVPEVAL_EXPECTED_OPENING_BRACKET);
        case EXPEVAL_UNEXPECTED_CLOSING_BRACKET:
            return STR(EXPEVAL_UNEXPECTED_CLOSING_BRACKET);
        case EXPEVAL_BRACKET_NOT_CLOSED:
            return STR(EXPEVAL_BRACKET_NOT_CLOSED);
        case EXPEVAL_HANGING_OPERATOR :
            return STR(EXPEVAL_HANGING_OPERATOR);
        case EXPEVAL_VALUE_EXPECTED:
            return STR(EXPEVAL_VALUE_EXPECTED);
        case EXPEVAL_OPERATOR_EXPECTED:
            return STR(EXPEVAL_OPERATOR_EXPECTED);
        case EXPEVAL_INTERNAL_ERROR:
            return STR(EXPEVAL_INTERNAL_ERROR);
        case EXPEVAL_IDENTIFIER_NOT_FOUND:
            return STR(EXPEVAL_IDENTIFIER_NOT_FOUND);
        case EXPEVAL_IDENTIFIER_TOO_LONG:
            return STR(EXPEVAL_IDENTIFIER_TOO_LONG);
        default:
            return STR(EXPEVAL_UNKNOWN);
    }
}
