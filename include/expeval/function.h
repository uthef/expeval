#ifndef EXPEVAL_FUNCTION_H
#define EXPEVAL_FUNCTION_H

typedef struct expeval_function expeval_function;

struct expeval_function {
    const char* name;
    double(*func)(double);
};

static const expeval_function EXPEVAL_FUNCTION_TERMINATOR = { 0, 0 };

#endif
