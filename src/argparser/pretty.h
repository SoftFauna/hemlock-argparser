
#pragma once

extern int g_pretty_print;

extern char *g_bold;
extern char *g_underline;
extern char *g_nobold;
extern char *g_nounderline;

extern char *g_fg_reset;
extern char *g_black;
extern char *g_red;
extern char *g_green;
extern char *g_yellow;
extern char *g_blue;
extern char *g_magenta;
extern char *g_cyan;
extern char *g_white;

extern char *g_bg_reset;
extern char *g_bg_black;
extern char *g_bg_red;
extern char *g_bg_green;
extern char *g_bg_yellow;
extern char *g_bg_blue;
extern char *g_bg_magenta;
extern char *g_bg_cyan;
extern char *g_bg_white;

void pretty_print_enable (void);
void pretty_print_disable (void);
