#include "result.h"

inline void expeval_result_init(expeval_result* p) {
    p->value = 0.;
    p->err_pos = 0;
    p->code = EXPEVAL_OK;
}
