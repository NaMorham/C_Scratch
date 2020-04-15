
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <Utils.h>

int g_log_level = (LOGLEVEL_DEFAULT);

size_t TIME_BUF_SZ = 64;

int getLogLevel()
{
    return g_log_level;
}

int setLogLevel(int newLevel)
{
    int oldLevel = g_log_level;
    g_log_level = LimitVal(LOG_FATAL, LOG_DEBUG, newLevel);
    return oldLevel;
}

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

        long            ms; // Milliseconds
        time_t          s;  // Seconds
        struct timespec spec;

        /* Clear buffers */
        memset(timeBuf, 0, sizeof(char)*TIME_BUF_SZ);
        memset(timeFmt, 0, sizeof(char)*TIME_BUF_SZ);

        /* Get the current system time using the realtime clock */
        clock_gettime(CLOCK_REALTIME, &spec);

        s  = spec.tv_sec;
        ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
        if (ms > 999)
        {
            s++;
            ms = 0;
        }

        sprintf(timeFmt, "%%Y-%%m-%%dT%%H:%%M:%%S.%03.3ld %%Z", ms);
        (void)strftime(timeBuf, TIME_BUF_SZ, timeFmt, gmtime(&s));

        fprintf(stderr, "[%s]%s[%s] ", timeBuf ,log_level_colour(level), log_level_text(level));
        vfprintf(stderr, format, args);
        fprintf(stderr, "%s\n", C_NRM);
        
        fflush(stderr);
    }
}

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
