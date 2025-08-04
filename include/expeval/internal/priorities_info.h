#ifndef EXPEVAL_PRIORITIES_INFO
#define EXPEVAL_PRIORITIES_INFO

typedef unsigned char uchar;
typedef struct priorities_info priorities_info;

struct priorities_info {
    uchar min_priority;
    uchar max_priority;
    uchar* priorities;
};

#endif
