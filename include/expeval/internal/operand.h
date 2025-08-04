#ifndef EXPEVAL_OPERAND_H
#define EXPEVAL_OPERAND_H

typedef struct operand operand;

struct operand {
    double value;
    double(*operation)(double, double);
    unsigned char priority;
    operand* next;
};

#endif 
