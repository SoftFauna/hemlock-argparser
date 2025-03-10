
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


typedef struct
{
    char *name;
    char *description;
    char *version;

    char *help_extra;
    char *version_extra;

    char *copyright_year;
    char *copyright_holder;
    char *license_name;
    char *license_url;

    char *issues_url;
    char *repository_url;
    char *contact_email;
    char *contact_name;

    copt_t *options;
    size_t  option_count;
} copt_prog_t;


/* end of file */
