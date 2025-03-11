/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team
 * MIT License */

#ifndef HMARG_DEBUG_TRACE_HEADER
#define HMARG_DEBUG_TRACE_HEADER
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

//#define WE_TRACIN
#ifdef WE_TRACIN
#   define TRACE_FN() (printf ("debug trace: %s: %hu\n", __func__, __LINE__))
#else
#   define TRACE_FN() do {} while (0)
#endif


#ifdef __clplusplus
}
#endif /* C++ compat */
#endif /* header guard */
/* end of file */
