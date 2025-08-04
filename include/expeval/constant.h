#ifndef EXPEVAL_CONSTANT_H
#define EXPEVAL_CONSTANT_H

typedef struct expeval_constant expeval_constant;

struct expeval_constant {
    const char* name;
    double value;
};

static const expeval_constant EXPEVAL_CONSTANT_TERMINATOR = { 0, 0 };

#endif
