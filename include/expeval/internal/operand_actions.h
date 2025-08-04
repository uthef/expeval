#ifndef EXPEVAL_INTERNAL_OPERATIONS
#define EXPEVAL_INTERNAL_OPERATIONS

#include "internal/operand.h"
#include "internal/priorities_info.h"
#include "result.h"

void update_priorities(operand* operand, uchar* priorities, priorities_info* prior_info);
int push_operand(operand**, size_t*, size_t*, double, uchar*, expeval_result*);
void calculate_result(operand*, size_t, uchar, priorities_info*, expeval_result*);

#endif
