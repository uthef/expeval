#include "internal/parser.h"

#include "stdlib.h"
#include "expeval.h"
#include "internal/number_parser.h"
#include "math_operations.h"
#include "internal/priorities_info.h"
#include "internal/operand_actions.h"
#include "internal/expeval_flags.h"
#include "internal/macros.h"
#include "internal/element.h"
#include "internal/name_resolver.h"
#include "internal/operand.h"

void parse_from(const char* exp, size_t* idx, expeval_result* result, unsigned int depth, expeval_context* ctx) {
    char c = 0;
    uchar flags = 0;
    size_t start_idx = *idx, operands_cap = 0, operands_count = 0, last_operator_pos = 0;
    operand* operands = 0;
    element last_element = ELEMENT_NONE;

    uchar priorities[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    priorities_info prior_info;
    prior_info.max_priority = EXPEVAL_MAX_PRIORITY;
    prior_info.min_priority = EXPEVAL_MAX_PRIORITY;
    prior_info.priorities = priorities;
    expeval_function* last_func = 0;

    while ((c = *(exp + (*idx)++))) {
        const size_t current_idx = *idx - 1;

        if (IS_SPACE_CHAR(c)) continue;

        if (IS_NUMERIC_CHAR(c) || c == '.') {
            if (last_element != ELEMENT_OPERATOR && last_element != ELEMENT_NONE) {
                result->code = EXPEVAL_OPERATOR_EXPECTED;
                result->err_pos = current_idx;
                break;
            }

            double value = expeval_parse_number(exp, idx, current_idx, result);
            if (result->code) break;

            if (!push_operand(&operands, &operands_cap, &operands_count, value, &flags, result)) {
                result->err_pos = current_idx;
                break;
            }

            last_element = ELEMENT_OPERAND;

            continue;
        }

        if (IS_OPERATOR_CHAR(c)) {
            if (last_element != ELEMENT_OPERAND) {
                if (c == '-' && IS_FLAG_NOT_SET(flags, NEGATE_NUMBER)) {
                    flags |= NEGATE_NUMBER;
                    continue;
                }
                else {
                    result->code = EXPEVAL_VALUE_EXPECTED;
                    result->err_pos = current_idx;
                    break;
                }
            }

            last_element = ELEMENT_OPERATOR;
            operand* last_operand = operands + (operands_count - 1);
            last_operator_pos = current_idx;
            
            switch (c) {
                case '+':
                    last_operand->operation = expeval_add;
                    last_operand->priority = EXPEVAL_LOW_PRIORITY_DEFAULT;
                    break;
                case '-':
                    last_operand->operation = expeval_subtract;
                    last_operand->priority = EXPEVAL_LOW_PRIORITY_DEFAULT;
                    break;
                case '/':
                    last_operand->operation = expeval_divide;
                    last_operand->priority = EXPEVAL_HIGH_PRIORITY_DEFAULT;
                    break;
                case '*':
                    last_operand->operation = expeval_multiply;
                    last_operand->priority = EXPEVAL_HIGH_PRIORITY_DEFAULT;
                    break;
            }

            update_priorities(last_operand, priorities, &prior_info);

            continue;
        }

        if (c == '(') {
            if (last_element != ELEMENT_OPERATOR && last_element != ELEMENT_NONE && !last_func) {
                result->code = EXPEVAL_OPERATOR_EXPECTED;
                result->err_pos = current_idx;
                break;
            }

            parse_from(exp, idx, result, depth + 1, ctx);
            if (result->code != EXPEVAL_OK) break;

            if (last_func) {
                result->value = last_func->func(result->value);
                last_func = 0;
            }

            if (!push_operand(&operands, &operands_cap, &operands_count, result->value, &flags, result)) {
                result->err_pos = current_idx;
                break;
            }

            last_element = ELEMENT_OPERAND;
            
            continue;
        }

        if (c == ')') {
            if (depth == 0) {
                result->code = EXPEVAL_UNEXPECTED_CLOSING_BRACKET;
                result->err_pos = current_idx;
                break;
            }

            flags |= HAS_CLOSING_BRACKET;
            break;
        }

        if (IS_NAME_CHAR(c)) {
            if (last_element != ELEMENT_OPERATOR && last_element != ELEMENT_NONE) {
                result->code = EXPEVAL_OPERATOR_EXPECTED;
                result->err_pos = current_idx;
                break;
            }

            const int buffer_size = 64;
            size_t b_idx = 1;
            char buffer[buffer_size];
            uchar is_func = 0, name_not_found = 0;

            buffer[0] = c;

            while ((c = *(exp + ((*idx)++))) && (IS_NAME_CHAR(c) || c == '(' || IS_NUMERIC_CHAR(c))) {
                if (c == '(') {
                    is_func = 1;
                    break;
                }

                if (b_idx >= buffer_size - 1) {
                    result->code = EXPEVAL_IDENTIFIER_TOO_LONG;
                    result->err_pos = current_idx;
                    break;
                }
                
                buffer[b_idx++] = c;
            }

            buffer[b_idx] = 0;
            (*idx)--;

            if (!ctx) name_not_found = 1;

            if (is_func && !name_not_found) {
                expeval_function* function = resolve_function(buffer, ctx->functions);
                if (!function) name_not_found = 1;
                else last_func = function;
            }
            else if (!name_not_found) {
                expeval_constant* constant = resolve_constant(buffer, ctx->constants);

                if (!constant) name_not_found = 1;
                else {
                    double value = constant->value;

                    if (!push_operand(&operands, &operands_cap, &operands_count, value, &flags, result)) {
                        result->err_pos = current_idx;
                        break;
                    }
                }
            }

            if (name_not_found) {
                result->code = EXPEVAL_IDENTIFIER_NOT_FOUND;
                result->err_pos = current_idx;
                break;
            }

            last_element = ELEMENT_OPERAND;
            continue;
        }

        const int buffer_size = 64;
        char buffer[buffer_size];
        size_t b_idx = 1;

        buffer[0] = c;

        while((c = *(exp + (*idx)++))) {
            if (b_idx >= buffer_size - 1) {
                result->code = EXPEVAL_INVALID_CHAR;
                result->err_pos = current_idx;
                break;
            }

            if (IS_OPERATOR_CHAR(c) || IS_NAME_CHAR(c) || IS_NUMERIC_CHAR(c) || IS_SPACE_CHAR(c) || c == '(' || c == ')' || c == '.') {
                break;
            }

            buffer[b_idx++] = c;
        }
        
        if (result->code != EXPEVAL_OK) break;

        (*idx)--;
        buffer[b_idx] = 0;

        expeval_operator* operator = 0;
        if (ctx) operator = resolve_operator(buffer, ctx->operators);

        if (operator) {
            if (last_element != ELEMENT_OPERAND) {
                result->code = EXPEVAL_VALUE_EXPECTED;
                result->err_pos = current_idx;
                break;
            }

            last_element = ELEMENT_OPERATOR;
            operand* last_operand = operands + (operands_count - 1);
            last_operator_pos = current_idx;

            last_operand->operation = operator->func;
            last_operand->priority = operator->priority;

            update_priorities(last_operand, priorities, &prior_info);

            continue;
        }
        
        result->code = EXPEVAL_INVALID_CHAR;
        result->err_pos = current_idx;
        break;
    }

    if (result->code == EXPEVAL_OK) {
        if (depth > 0 && IS_FLAG_NOT_SET(flags, HAS_CLOSING_BRACKET)) {
            result->code = EXPEVAL_BRACKET_NOT_CLOSED;
            result->err_pos = start_idx - 1;
        }
        else if (last_element == ELEMENT_OPERATOR) {
            result->code = EXPEVAL_HANGING_OPERATOR;
            result->err_pos = last_operator_pos;
        }
    }
    
    if (result->code != EXPEVAL_OK) {
        result->value = 0;
        if (operands) free(operands);
        return;
    }

    calculate_result(operands, operands_count, flags, &prior_info, result);

    if (operands) free(operands);
}
