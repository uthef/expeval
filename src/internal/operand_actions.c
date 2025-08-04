#include "internal/operand_actions.h"

#include "stdlib.h"
#include "internal/macros.h"
#include "internal/expeval_flags.h"
#include "expeval.h"

void update_priorities(operand* operand, uchar* priorities, priorities_info* prior_info) {
    uchar priority = (operand->priority > EXPEVAL_MAX_PRIORITY) ? EXPEVAL_MAX_PRIORITY : operand->priority;

    if (priority < EXPEVAL_MAX_PRIORITY) {
        priorities[priority] = 1;

        if (priority > prior_info->max_priority || prior_info->max_priority == EXPEVAL_MAX_PRIORITY) {
            prior_info->max_priority = priority;
        }

        if (priority < prior_info->min_priority || prior_info->min_priority == EXPEVAL_MAX_PRIORITY) {
            prior_info->min_priority = priority;
        }
    }
}

void calculate_result(operand* operands, size_t op_count, uchar flags, priorities_info* prior, expeval_result* result) {
    if (!operands) {
        result->value = 0;
        return;
    }

    operand* first_operand = 0;
    operand* prev_operand = 0;

    for (int p = prior->max_priority; p >= prior->min_priority && prior->min_priority < EXPEVAL_MAX_PRIORITY; p--) {
        if (!prior->priorities[p]) continue;

        uchar highest = 0;

        if (IS_FLAG_NOT_SET(flags, HAD_HIGHEST_PRIORITY_BEFORE)) {
            flags |= HAD_HIGHEST_PRIORITY_BEFORE;
            highest = 1;
        }
        
        operand* _operand = first_operand ? first_operand : operands;
        prev_operand = 0;
        size_t idx = 0;

        while (_operand) {
            operand* next = 0;

            if (highest) {
                if (idx < op_count - 1) {
                    next = operands + (idx + 1);
                }
            }
            else next = _operand->next;

            if (_operand->priority == p && next) {
                if (!_operand->operation) {
                    result->code = EXPEVAL_INTERNAL_ERROR;
                    result->err_pos = 0;
                    break;
                }

                next->value = _operand->operation(_operand->value, next->value);
                if (prev_operand) prev_operand->next = next;
            }
            else {
                if (!first_operand) first_operand = _operand;
                if (prev_operand) prev_operand->next = _operand;

                prev_operand = _operand;
            }

            if (highest) {
                idx++;
                if (idx >= op_count) _operand = 0;
                else _operand = operands + idx;
            }
            else _operand = _operand->next;
        }

        if (result->code != EXPEVAL_OK) break;
    }

    if (result->code != EXPEVAL_OK) result->value = 0;
    else if (prev_operand) result->value = prev_operand->value;
    else if (op_count > 0) result->value = operands->value;
}

int push_operand(operand** operands, size_t* cap, size_t* count, double value, uchar* flags, expeval_result* result) {
    if (IS_FLAG_SET(*flags, NEGATE_NUMBER)) {
        value = -value;
        *flags &= ~NEGATE_NUMBER;
    }

    if (*count > 0) {
        operand* last_operand = (*operands) + (*count - 1);

        if (!last_operand->operation) {
            result->code = EXPEVAL_INTERNAL_ERROR;
            return 0;
        }

        if (last_operand->priority >= EXPEVAL_MAX_PRIORITY) {
            last_operand->value = last_operand->operation(last_operand->value, value);
            last_operand->operation = 0;
            last_operand->priority = 0;

            return 1;
        }
    }

    if (!*operands || *count >= *cap) {
        if (*cap == 0) *cap = 10;
        else *cap *= 2;

        operand* new_arr = realloc(*operands, sizeof(operand) * (*cap));

        if (!new_arr) {
            result->code = EXPEVAL_MEMORY_ALLOCATION_IMPOSSIBLE;
            return 0;
        }

        *operands = new_arr;
    }

    operand o;
    o.value = value;
    o.operation = 0; o.priority = 0; o.next = 0;

    *((*operands) + *count) = o;

    (*count)++;

    return 1;
}
