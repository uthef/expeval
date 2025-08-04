#ifndef EXPEVAL_NAME_RESOLVER_H
#define EXPEVAL_NAME_RESOLVER_H

#include "function.h"
#include "constant.h"
#include "operator.h"

expeval_function* resolve_function(const char*, expeval_function*);
expeval_constant* resolve_constant(const char*, expeval_constant*);
expeval_operator* resolve_operator(const char*, expeval_operator*);

#endif
