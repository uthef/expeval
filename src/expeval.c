#include "expeval.h"

#include "internal/parser.h"

expeval_result expeval(const char* exp, expeval_context* ctx) {
    expeval_result result;
    size_t idx = 0;

    expeval_result_init(&result);
    parse_from(exp, &idx, &result, 0, ctx);

    return result;
}
