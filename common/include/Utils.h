/****************************************************************************
 *                                                                          *
 ****************************************************************************/

#ifndef __ANH_GS__UTILS_H__
#define __ANH_GS__UTILS_H__

/* booleans */
#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* Log levels */
#define LOG_FATAL 0
#define LOG_ERROR 1
#define LOG_WARN  2
#define LOG_INFO  3
#define LOG_TRACE 4
#define LOG_DEBUG 5

#define LOGLEVEL_DEFAULT (LOG_INFO)

extern  int g_log_level;

/* Colour vals */
#ifdef USE_COLOUR
    #define C_NRM "\033[0m"

    #define C_BLD "\033[1m"
    #define C_ITL "\033[3m"
    #define C_UND "\033[4m"

    #define C_BLK "\033[30m"
    #define C_RED "\033[31m"
    #define C_GRN "\033[32m"
    #define C_YEL "\033[33m"
    #define C_BLU "\033[34m"
    #define C_MAG "\033[35m"
    #define C_CYN "\033[36m"
    #define C_WHT "\033[37m"
#else
    #define C_NRM ""

    #define C_BLD ""
    #define C_ITL ""
    #define C_UND ""

    #define C_BLK ""
    #define C_RED ""
    #define C_GRN ""
    #define C_YEL ""
    #define C_BLU ""
    #define C_MAG ""
    #define C_CYN ""
    #define C_WHT ""
#endif

/* Limits and values */
#define MaxVal (a,b) ( a < b ? b : a )

#define MinVal (a,b) ( a < b ? a : b )

#define LimitVal (mn, mx, v) ( v > mx ? mx : ( v < mn ? mn : v ) )

extern char* log_level_text(int level);
extern char* log_level_colour(int level);

extern void basic_log(int level, char *format, ...) __attribute__ ((format (printf, 2, 3)));
extern void basic_vlog(int level, char *format, va_list args);

extern void error_log(char *format, ...) __attribute__ ((format (printf, 1, 2)));
extern void warn_log(char *format, ...) __attribute__ ((format (printf, 1, 2)));
extern void info_log(char *format, ...) __attribute__ ((format (printf, 1, 2)));
extern void trace_log(char *format, ...) __attribute__ ((format (printf, 1, 2)));
extern void debug_log(char *format, ...) __attribute__ ((format (printf, 1, 2)));

#endif // __ANH_GS__UTILS_H__
