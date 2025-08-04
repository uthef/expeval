#include "internal/number_parser.h"

#include "result.h"
#include "internal/macros.h"
#include "stdlib.h"

#define NUM_DOT 0x01
#define NUM_EMPTY 0x02
#define NUM_E 0x04
#define NUM_E_SIGN 0x08
#define NUM_E_DIGITS 0x10
#define NUM_DELIM_LAST 0x20
#define NUM_INVALID 0x40

double expeval_parse_number(const char* exp, size_t* idx, size_t current_idx, expeval_result* result) {
    int buffer_size = 64;
    char buffer[64];
    char c = *(exp + current_idx);

    unsigned char flags = 0;
    int b_idx = 1;

    if (c == '.') flags |= NUM_DOT | NUM_EMPTY;
    buffer[0] = c;

    while((c = *(exp + (*idx)++))) {
        if (c == '.') {
            if (IS_FLAG_SET(flags, NUM_DOT) || IS_FLAG_SET(flags, NUM_E)) {
                flags |= NUM_INVALID;
                break;
            }

            flags |= NUM_DOT;
        }
        else if (IS_NUMERIC_CHAR(c)) {
            flags &= ~NUM_EMPTY;
            if (IS_FLAG_SET(flags, NUM_E_SIGN) || IS_FLAG_SET(flags, NUM_E)) flags |= NUM_E_DIGITS;
        }
        else if (c == ',') {
            if (IS_FLAG_SET(flags, NUM_E) || IS_FLAG_SET(flags, NUM_DOT) || IS_FLAG_SET(flags, NUM_DELIM_LAST)) {
                flags |= NUM_INVALID;
                break;
            }

            flags |= NUM_DELIM_LAST;
            continue;
        }
        else if (c == 'e' || c == 'E') {
            if (IS_FLAG_SET(flags, NUM_E)) {
                flags |= NUM_INVALID;
                break;
            }

            flags |= NUM_E;
        }
        else if (c == '-' || c == '+') {
            if (IS_FLAG_NOT_SET(flags, NUM_E) || IS_FLAG_SET(flags, NUM_E_DIGITS)) break;

            if (IS_FLAG_SET(flags, NUM_E_SIGN)) {
                flags |= NUM_INVALID;
                break;
            }

            flags |= NUM_E_SIGN;
        }
        else break;

        if (b_idx >= buffer_size - 1) {
            result->code = EXPEVAL_NUMBER_TOO_BIG;
            result->err_pos = current_idx;
            return 0;
        }

        buffer[b_idx++] = c;
        flags &= ~NUM_DELIM_LAST;
    }

    (*idx)--;
    
    if (IS_FLAG_SET(flags, NUM_EMPTY) || (IS_FLAG_SET(flags, NUM_E) && IS_FLAG_NOT_SET(flags, NUM_E_DIGITS))) {
        flags |= NUM_INVALID;
    }

    if (IS_FLAG_SET(flags, NUM_DELIM_LAST)) flags |= NUM_INVALID;

    if (IS_FLAG_SET(flags, NUM_INVALID)) {
        result->code = EXPEVAL_INVALID_NUMBER;
        result->err_pos = current_idx;
        return 0;
    }

    buffer[b_idx] = 0;
    return strtod(buffer, NULL);
}
