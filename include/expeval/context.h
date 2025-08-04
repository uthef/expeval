#ifndef EXPEVAL_CONTEXT_H
#define EXPEVAL_CONTEXT_H

#include "constant.h"
#include "operator.h"
#include "function.h"

typedef struct expeval_context expeval_context;

struct expeval_context {
    expeval_constant* constants;
    expeval_function* functions;
    expeval_operator* operators;
};

#endif
