
#include "pretty.h"

#include <stddef.h>

#define ESC         "\033["
#define RESET       ESC"0m"

#define BOLD        ESC"1m"
#define NOBOLD      ESC"22m"
#define UNDERLINE   ESC"4m"
#define NOUNDERLINE ESC"24m"

#define FG_RESET    ESC"39m"
#define BLACK       ESC"30m"
#define RED         ESC"31m"
#define GREEN       ESC"32m"
#define YELLOW      ESC"33m"
#define BLUE        ESC"34m"
#define MAGENTA     ESC"35m"
#define CYAN        ESC"36m"
#define WHITE       ESC"37m"

#define BG_RESET    ESC"49m"
#define BG_BLACK    ESC"40m"
#define BG_RED      ESC"41m"
#define BG_GREEN    ESC"42m"
#define BG_YELLOW   ESC"43m"
#define BG_BLUE     ESC"44m"
#define BG_MAGENTA  ESC"45m"
#define BG_CYAN     ESC"46m"
#define BG_WHITE    ESC"47m"

/* PUBLIC API */
int g_pretty_print = 0;

char *g_bold       = "";
char *g_nobold     = "";
char *g_underline  = "";
char *g_nounderline = "";

char *g_fg_reset   = "";
char *g_black   = "";
char *g_red     = "";
char *g_green   = "";
char *g_yellow  = "";
char *g_blue    = "";
char *g_magenta = "";
char *g_cyan    = "";
char *g_white   = "";

char *g_bg_reset   = "";
char *g_bg_black   = "";
char *g_bg_red     = "";
char *g_bg_green   = "";
char *g_bg_yellow  = "";
char *g_bg_blue    = "";
char *g_bg_magenta = "";
char *g_bg_cyan    = "";
char *g_bg_white   = "";


void
pretty_print_enable (void)
{
    g_pretty_print = 1;

    g_bold        = BOLD;
    g_nobold      = NOBOLD;
    g_underline   = UNDERLINE;
    g_nounderline = NOUNDERLINE;
    
    g_fg_reset = FG_RESET;
    g_black    = BLACK;
    g_red      = RED;
    g_green    = GREEN;      
    g_yellow   = YELLOW;      
    g_blue     = BLUE;        
    g_magenta  = MAGENTA;     
    g_cyan     = CYAN;        
    g_white    = WHITE;       
    
    g_bg_reset   = BG_RESET;    
    g_bg_black   = BG_BLACK;    
    g_bg_red     = BG_RED;      
    g_bg_green   = BG_GREEN;    
    g_bg_yellow  = BG_YELLOW;   
    g_bg_blue    = BG_BLUE;     
    g_bg_magenta = BG_MAGENTA;  
    g_bg_cyan    = BG_CYAN;     
    g_bg_white   = BG_WHITE;    
}


void
pretty_print_disable (void)
{
    g_pretty_print = 0;

    g_bold        = "";
    g_nobold      = "";
    g_underline   = "";
    g_nounderline = "";

    g_fg_reset = "";
    g_black    = "";
    g_red      = "";
    g_green    = "";  
    g_yellow   = "";   
    g_blue     = "";   
    g_magenta  = "";   
    g_cyan     = "";   
    g_white    = "";   

    g_bg_reset   = "";   
    g_bg_black   = "";   
    g_bg_red     = "";   
    g_bg_green   = "";   
    g_bg_yellow  = "";   
    g_bg_blue    = "";   
    g_bg_magenta = "";  
    g_bg_cyan    = "";   
    g_bg_white   = "";   
}


/* PRIVATE API */


/* end of file */
