#ifndef EXPEVAL_PARSER_H
#define EXPEVAL_PARSER_H

#include "result.h"
#include "context.h"

void parse_from(const char*, size_t*, expeval_result*, unsigned int, expeval_context*);

#endif
