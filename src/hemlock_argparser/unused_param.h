/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team
 * MIT License */

#ifndef HMARG__HEADER
#define HMARG__HEADER
#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __clplusplus
}
#endif /* C++ compat */
#endif /* header guard */
/* end of file */
