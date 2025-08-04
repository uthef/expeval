#include "expeval_ext.h"
#include "stdio.h"
#include "string.h"


void expeval_ext(const char* expression, expeval_result* out, expeval_constant* constants, expeval_function* functions, 
    expeval_operator* operators) {

    expeval_context ctx;
    ctx.constants = constants;
    ctx.functions = functions;
    ctx.operators = operators;

    expeval_result result = expeval(expression, &ctx);
    
    out->code = result.code;
    out->err_pos = result.err_pos;
    out->value = result.value;
}
