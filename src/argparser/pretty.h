
#pragma once

#include <stdio.h>
#include <stdarg.h>

int cfprintf (FILE *stream, const char * restrict format, ...);

void cprintf_enable (void);
void cprintf_disable (void);
int cprintf_get_status (void);

/* end of file */