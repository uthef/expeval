#ifndef EXPEVAL_RESULT_H
#define EXPEVAL_RESULT_H

#include "stddef.h"
#include "result_code.h"

typedef struct expeval_result expeval_result;

struct expeval_result {
    double value;
    size_t err_pos;
    expeval_result_code code;
};

void expeval_result_init(expeval_result*);

#endif
