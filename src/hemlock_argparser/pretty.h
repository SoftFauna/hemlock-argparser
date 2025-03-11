/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team
 * MIT License */

#ifndef HMARG_PRETTY_HEADER
#define HMARG_PRETTY_HEADER
#ifdef __cplusplus
extern "C" {
#endif
 

#include <stdio.h>
#include <stdarg.h>

int cfprintf (FILE *stream, const char * restrict format, ...);

int csnprintf_v2 (char *buf, size_t buf_n, int *p_size, int *p_plen, const char * restrict format, ...);
int csnprintf (char *buf, size_t buf_n, const char * restrict format, ...);
int cvsnprintf (char *buf, size_t buf_n, const char * restrict format, va_list args); 

void cprintf_enable (void);
void cprintf_disable (void);
int cprintf_get_status (void);

#ifdef __clplusplus
}
#endif /* C++ compat */
#endif /* header guard */
/* end of file */
