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

    #define C_BBLK "\033[90m"
    #define C_BRED "\033[91m"
    #define C_BGRN "\033[92m"
    #define C_BYEL "\033[93m"
    #define C_BBLU "\033[94m"
    #define C_BMAG "\033[95m"
    #define C_BCYN "\033[96m"
    #define C_BWHT "\033[97m"

    #define CB_BLK "\033[40m"
    #define CB_RED "\033[41m"
    #define CB_GRN "\033[42m"
    #define CB_YEL "\033[43m"
    #define CB_BLU "\033[44m"
    #define CB_MAG "\033[45m"
    #define CB_CYN "\033[46m"
    #define CB_WHT "\033[47m"

    #define CB_BBLK "\033[100m"
    #define CB_BRED "\033[101m"
    #define CB_BGRN "\033[102m"
    #define CB_BYEL "\033[103m"
    #define CB_BBLU "\033[104m"
    #define CB_BMAG "\033[105m"
    #define CB_BCYN "\033[106m"
    #define CB_BWHT "\033[107m"
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

    #define C_BBLK ""
    #define C_BRED ""
    #define C_BGRN ""
    #define C_BYEL ""
    #define C_BBLU ""
    #define C_BMAG ""
    #define C_BCYN ""
    #define C_BWHT ""

    #define CB_BLK ""
    #define CB_RED ""
    #define CB_GRN ""
    #define CB_YEL ""
    #define CB_BLU ""
    #define CB_MAG ""
    #define CB_CYN ""
    #define CB_WHT ""

    #define CB_BBLK ""
    #define CB_BRED ""
    #define CB_BGRN ""
    #define CB_BYEL ""
    #define CB_BBLU ""
    #define CB_BMAG ""
    #define CB_BCYN ""
    #define CB_BWHT ""
#endif

/* Log levels */
#define LOG_FATAL 0
#define LOG_ERROR 1
#define LOG_WARN  2
#define LOG_INFO  3
#define LOG_DEBUG 4
#define LOG_TRACE 5

#define LOGLEVEL_DEFAULT (LOG_INFO)

#define LC_FTL (C_BRED)
#define LC_ERR (C_RED)
#define LC_WRN (C_MAG)
#define LC_INF (C_YEL)
#define LC_TRC (C_CYN)
#define LC_DBG (C_GRN)
#define LC_UNK (C_BLU)

#ifndef BOOL
typedef unsigned char BOOL;
#endif

extern int g_log_level;

/* Limits and values - macros - bad :( */
#define MinVal(a,b) (((a)<(b))?(a):(b))
#define MaxVal(a,b) (((a)>(b))?(a):(b))

#define LimitVal(i, x, v) ( ( (x) > (i) ) ? \
    ( MaxVal( ( MinVal( (v), (x) ) ), (i) ) ) : \
    ( MaxVal( ( MinVal( (v), (i) ) ), (x) ) ) )

/* Logging control and use */
extern const int getLogLevel();
extern const int setLogLevel(const int newLevel);

/**
 * Get the 5 character string representqtion of the log level.
 *
 * @param level The log level to retrieve.
 * @return A 5 character representation of the log level.
 */
extern const char* log_level_text(const int level);

/**
 * Get colour string/code for use when logging to stderr based on the log level.
 *
 * @param level The log level to retrieve.
 * @return An ANSI colour escape code for the log level.
 */
extern const char* log_level_colour(const int level);

/** 
 * Log messages directly to stderr on disk, no display to in game immortals.
 * Supports variable string modification arguments, a la printf. Most likely
 * any calls to plain old log() have been redirected, via macro, to this
 * function.
 *
 * @param funcname The name of the calling function.
 * @param level The logging level of the message.
 * @param format The message to log. Standard printf formatting and variable
 * arguments are allowed.
 * @param ... The comma delimited, variable substitutions to make in str.
 */
extern void basic_log(const char *funcname, const int level, const char *format, ...) __attribute__ ((format (printf, 3, 4)));

/**
 * New variable argument log() function; logs messages to disk.
 * Works the same as the old for previously written code but is very nice
 * if new code wishes to implment printf style log messages without the need
 * to make prior sprintf calls.
 *
 * @param funcname The name of the calling function.
 * @param level The logging level of the message.
 * @param format The message to log. Standard printf formatting and variable
 * arguments are allowed.
 * @param args The comma delimited, variable substitutions to make in str.
 */
extern void basic_vlog(const char *funcname, const int level, const char *format, va_list args);

/**
 * Write a error log level message using var args and sprintf formatting.
 *
 * @param format The message to log. Standard printf formatting and variable
 * arguments are allowed.
 * @param args The comma delimited, variable substitutions to make in str.
 */
#define error_log(fmt, ...) basic_log(__FUNCTION__, LOG_ERROR, fmt, ##__VA_ARGS__)

/**
 * Write a warning log level message using var args and sprintf formatting.
 *
 * @param format The message to log. Standard printf formatting and variable
 * arguments are allowed.
 * @param args The comma delimited, variable substitutions to make in str.
 */
#define warn_log(fmt, ...) basic_log(__FUNCTION__, LOG_WARN, fmt, ##__VA_ARGS__)

/**
 * Write a info log level message using var args and sprintf formatting.
 *
 * @param format The message to log. Standard printf formatting and variable
 * arguments are allowed.
 * @param args The comma delimited, variable substitutions to make in str.
 */
#define info_log(fmt, ...) basic_log(__FUNCTION__, LOG_INFO, fmt, ##__VA_ARGS__)

/**
 * Write a trace log level message using var args and sprintf formatting.
 *
 * @param format The message to log. Standard printf formatting and variable
 * arguments are allowed.
 * @param args The comma delimited, variable substitutions to make in str.
 */
#define trace_log(fmt, ...) basic_log(__FUNCTION__, LOG_TRACE, fmt, ##__VA_ARGS__)

/**
 * Write a debug log level message using var args and sprintf formatting.
 *
 * @param format The message to log. Standard printf formatting and variable
 * arguments are allowed.
 * @param args The comma delimited, variable substitutions to make in str.
 */
#define debug_log(fmt, ...) basic_log(__FUNCTION__, LOG_DEBUG, fmt, ##__VA_ARGS__)

#endif // __ANH_GS__UTILS_H__
