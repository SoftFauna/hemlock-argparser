
#pragma once

#include <stddef.h>

typedef enum
{
    CONARG_TYPE_NULL = 0,
    INPUT_INT,
    INPUT_STR,
    FLAG_T,
    FLAG_F,
    CALLBACK,
    CONARG_TYPE_CNT,
} copt_type_t;

typedef struct copt
{
    char short_opt;
    char *long_opt;
    copt_type_t type;
    union
    {
        void *return_ptr;
        char **p_str;
        int *p_int;
        int (*cb_fn)(struct copt*, size_t, void*);
    } m;
    char *desc;
} copt_t;

/* end of file */