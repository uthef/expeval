#ifndef EXPEVAL_H
#define EXPEVAL_H

#include "result.h"
#include "context.h"

static const unsigned char EXPEVAL_MIN_PRIORITY = 0;
static const unsigned char EXPEVAL_MAX_PRIORITY = 9;
static const unsigned char EXPEVAL_LOW_PRIORITY_DEFAULT = 3;
static const unsigned char EXPEVAL_HIGH_PRIORITY_DEFAULT = 6;

expeval_result expeval(const char* expression, expeval_context*);

#endif
