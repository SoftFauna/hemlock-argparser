
#pragma once

#include <stdio.h>

#define CB_UNUSED_PARAM(variable_name) \
    while (0) \
    { \
        (void)fprintf (stderr, \
                "fatal error: this should never execute.\n" \
                "unused cb_parameter: %s: %s: %p\n", \
                __func__, #variable_name, (void *)&variable_name); \
        break; \
    }

/* end of file */
