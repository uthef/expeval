#ifndef EXPEVAL_OPERATOR_H
#define EXPEVAL_OPERATOR_H

typedef struct expeval_operator expeval_operator;

struct expeval_operator {
    const char* id;
    unsigned char priority;
    double(*func)(double, double);
};

static const expeval_operator EXPEVAL_OPERATOR_TERMINATOR = { 0, 0, 0 };

#endif
