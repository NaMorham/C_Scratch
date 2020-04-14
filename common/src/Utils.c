
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>


#include <Utils.h>

int g_log_level = (LOGLEVEL_DEFAULT);

size_t TIME_BUF_SZ = 64;


char* log_level_text(int level)
{
    if (level == LOG_FATAL)
        return "FATAL";
    else if (level == LOG_ERROR)
        return "ERROR";
    else if (level == LOG_WARN)
        return "WARN ";
    else if (level == LOG_INFO)
        return "INFO ";
    else if (level == LOG_TRACE)
        return "TRACE";
    else if (level == LOG_DEBUG)
        return "DEBUG";
    else
        return "UNKN ";
}


char* log_level_colour(int level)
{
    if (level == LOG_FATAL)
        return (LC_FTL);
    else if (level == LOG_ERROR)
        return (LC_ERR);
    else if (level == LOG_WARN)
        return (LC_WRN);
    else if (level == LOG_INFO)
        return (LC_INF);
    else if (level == LOG_TRACE)
        return (LC_TRC);
    else if (level == LOG_DEBUG)
        return (LC_DBG);
    else
        return (LC_UNK);
}


/**
 * New variable argument log() function; logs messages to disk.
 * Works the same as the old for previously written code but is very nice
 * if new code wishes to implment printf style log messages without the need
 * to make prior sprintf calls.
 *
 * @param format The message to log. Standard printf formatting and variable
 * arguments are allowed.
 * @param args The comma delimited, variable substitutions to make in str.
 */
void basic_vlog(int level, char *format, va_list args)
{
    if (format == NULL)
    {
        format = "SYSERR: received a NULL format.";
        level = LOG_ERROR;
    }

    if (level <= g_log_level)
    {
        char timeBuf[TIME_BUF_SZ];
        char timeFmt[TIME_BUF_SZ];

        memset(timeBuf, 0, sizeof(char)*TIME_BUF_SZ);
        /*memset(timeFmt, 0, sizeof(char)*TIME_BUF_SZ);

        sprintf();

		struct timeval  tv;
		gettimeofday(&tv, NULL);*/

        time_t ct = time(0);
        (void)strftime(timeBuf, TIME_BUF_SZ, "%Y-%m-%dT%H:%M:%S.", gmtime(&ct));

        //char *time_s = asctime(localtime(&ct));

        //timeBuf[strlen(timeBuf) - 1] = '\0';

        /*
        fprintf(stderr, "[%s]%s[%s]%s ", timeBuf, ,log_level_colour(level), log_level_text(level), C_NRM);
        vfprintf(stderr, format, args);
        fputc('\n', stderr);
         */
        fprintf(stderr, "[%s]%s[%s] ", timeBuf ,log_level_colour(level), log_level_text(level));
        vfprintf(stderr, format, args);
        fprintf(stderr, "%s\n", C_NRM);
        
        fflush(stderr);
    }
}


/** 
 * Log messages directly to stderr on disk, no display to in game immortals.
 * Supports variable string modification arguments, a la printf. Most likely
 * any calls to plain old log() have been redirected, via macro, to this
 * function.
 *
 * @param format The message to log. Standard printf formatting and variable
 * arguments are allowed.
 * @param ... The comma delimited, variable substitutions to make in str.
 */
void basic_log(int level, char *format, ...)
{
    va_list args;

    va_start(args, format);
    basic_vlog(level, format, args);
    va_end(args);
}

void error_log(char *format, ...)
{
    va_list args;

    va_start(args, format);
    basic_vlog(LOG_ERROR, format, args);
    va_end(args);
}

void warn_log(char *format, ...)
{
    va_list args;

    va_start(args, format);
    basic_vlog(LOG_WARN, format, args);
    va_end(args);
}

void info_log(char *format, ...)
{
    va_list args;

    va_start(args, format);
    basic_vlog(LOG_INFO, format, args);
    va_end(args);
}

void trace_log(char *format, ...)
{
    va_list args;

    va_start(args, format);
    basic_vlog(LOG_TRACE, format, args);
    va_end(args);
}

void debug_log(char *format, ...)
{
    va_list args;

    va_start(args, format);
    basic_vlog(LOG_DEBUG, format, args);
    va_end(args);
}
