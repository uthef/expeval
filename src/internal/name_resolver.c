#include "internal/name_resolver.h"

#include "string.h"

expeval_function* resolve_function(const char* name, expeval_function* functions) {
    expeval_function* func_ptr = functions;

    while (func_ptr && func_ptr->name && func_ptr->func) {
        if (strcmp(name, func_ptr->name) == 0) return func_ptr;
        func_ptr++;
    }

    return 0;
}

expeval_constant* resolve_constant(const char* name, expeval_constant* constants) {
    expeval_constant* const_ptr = constants;

    while (const_ptr && const_ptr->name) {
        if (strcmp(name, const_ptr->name) == 0) return const_ptr;
        const_ptr++;
    }

    return 0;
}

expeval_operator* resolve_operator(const char* id, expeval_operator* operators) {
    expeval_operator* oper_ptr = operators;

    while (oper_ptr && oper_ptr->id && oper_ptr->func) {
        if (strcmp(id, oper_ptr->id) == 0) return oper_ptr;
        oper_ptr++;
    }

    return 0;
}
