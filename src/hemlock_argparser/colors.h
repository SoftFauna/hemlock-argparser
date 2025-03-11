/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team
 * MIT License */

#ifndef HMARG_THEME_HEADER
#define HMARG_THEME_HEADER
#ifdef __cplusplus
extern "C" {
#endif

#define C_OPTION "%Ab%Fm"
#define C_PARAM  "%Ab%Ai%Fc"
#define C_LABEL  "%Ab"

#define C_BINARY "%Ab%Fy"
#define C_LINK   "%Ai%Fc"
#define C_NAME   "%Fc"
#define C_EMAIL  C_LINK

#define C_FATAL  "%Au%Ab%Fr"
#define C_ERROR  "%Ab%Fr"
#define C_WARN   "%Ab%Fy"

#define C_RESET  "%Ar"


#ifdef __clplusplus
}
#endif /* C++ compat */
#endif /* header guard */
/* end of file */
