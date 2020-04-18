
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

const int getLogLevel()
{
    return g_log_level;
}

const int setLogLevel(const int newLevel)
{
    int oldLevel = g_log_level;
    g_log_level = LimitVal(LOG_FATAL, LOG_DEBUG, newLevel);
    return oldLevel;
}

const char* log_level_text(const int level)
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

const char* log_level_colour(const int level)
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

void basic_vlog(const char *funcname, const int level, const char *format, va_list args)
{
    int _level = level;

    if (format == NULL)
    {
        format = "SYSERR: received a NULL format.";
        _level = LOG_ERROR;
    }

    if (_level <= g_log_level)
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

        fprintf(stderr, "[%s]%s[%s][%-16.16s] ", timeBuf ,log_level_colour(level), log_level_text(level), funcname);
        vfprintf(stderr, format, args);
        fprintf(stderr, "%s\n", C_NRM);
        
        fflush(stderr);
    }
}

void basic_log(const char *funcname, const int level, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    basic_vlog(funcname, level, format, args);
    va_end(args);
}

