
#pragma once

#include <stdio.h>

/* #define WE_TRACIN */
#ifdef WE_TRACIN
#   define TRACE_FN() (printf ("debug trace: %s: %hu\n", __func__, __LINE__))
#else
#   define TRACE_FN() do {} while (0)
#endif

/* end of file */
