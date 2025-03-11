/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team
 * MIT License */

#include "pretty.h"

#define CPRINTF_IMPLEMENTATION
#define CPRINTF_ENABLE_FLAG_DEFAULT 0
#include <cprintf.h>


int
csnprintf_v2 (char *buf, size_t buf_n, int *p_size, int *p_plen, 
        const char * restrict format, ...)
{
    va_list args, args_copy;
    int size = 0;
    int plen = 0;

    va_start (args, format);
    va_copy (args_copy, args);

    size = cvsnprintf (buf, buf_n, format, args);
    if (cprintf_get_status () == 0)
    {
        plen = size;
    }
    else
    {
        cprintf_disable ();
        plen = cvsnprintf (NULL, 0, format, args_copy);
        cprintf_enable ();
    }

    va_end (args_copy);
    va_end (args);

    if (p_size != NULL) { *p_size = size; }
    if (p_plen != NULL) { *p_plen = plen; }
    return 0;
}


/* end of file */
