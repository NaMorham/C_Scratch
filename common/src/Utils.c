
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <Utils.h>

int g_log_level = (LOGLEVEL_DEFAULT);

#define TIME_BUF_SZ 64

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


const char* IsNullStr(const void* ptr)
{
    return (ptr ? "not null" : "null");
}

const char* log_level_text(int level)
{
    if (level == LOG_FATAL)
        return "FATAL";
    else if (level == LOG_ERROR)
        return "ERROR";
    else if (level == LOG_WARN)
        return "WARN ";
    else if (level == LOG_INFO)
        return "INFO ";
    else if (level == LOG_DEBUG)
        return "DEBUG";
    else if (level == LOG_TRACE)
        return "TRACE";
    else
        return "UNKN ";
}

const char* log_level_colour(int level)
{
    if (level == LOG_FATAL)
        return (LC_FTL);
    else if (level == LOG_ERROR)
        return (LC_ERR);
    else if (level == LOG_WARN)
        return (LC_WRN);
    else if (level == LOG_INFO)
        return (LC_INF);
    else if (level == LOG_DEBUG)
        return (LC_DBG);
    else if (level == LOG_TRACE)
        return (LC_TRC);
    else
        return (LC_UNK);
}

const char* get_timestamp(char* timeBuf, int bufSz)
{
    char timeFmt[TIME_BUF_SZ];

#ifdef _MSC_VER
    time_t now = time(NULL);
    struct tm newtm;
    long timezone;

    _get_timezone(&timezone);

    /* Clear buffers */
    memset(timeFmt, 0, sizeof(char)*TIME_BUF_SZ);

    localtime_s(&newtm, &now);
    sprintf_s(timeFmt, TIME_BUF_SZ, "%%Y-%%m-%%dT%%H:%%M:%%S%s%02d:%02d",
        (timezone<0 ? "+" : ""), -1 * timezone % 3600, -1 * timezone / 3600);
    strftime(timeBuf, bufSz, timeFmt, &newtm);
#else
    long            ms; // Milliseconds
    time_t          s;  // Seconds
    struct timespec spec;

    /* Clear buffers */
    memset(timeFmt, 0, sizeof(char)*TIME_BUF_SZ);

    /* Get the current system time using the realtime clock */
    clock_gettime(CLOCK_REALTIME, &spec);

    s = spec.tv_sec;
    ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
    if (ms > 999)
    {
        s++;
        ms = 0;
    }

    sprintf(timeFmt, "%%Y-%%m-%%dT%%H:%%M:%%S.%03.3ld %%z", ms);
    (void)strftime(timeBuf, TIME_BUF_SZ, timeFmt, gmtime(&s));
#endif // _MCS_VER

    return timeBuf;
}

void basic_vlog(const char *funcname, int level, const char *format, va_list args)
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
        memset(timeBuf, 0, sizeof(char)*TIME_BUF_SZ);

        fprintf(stderr, "[%s]%s[%s] ", get_timestamp(timeBuf, TIME_BUF_SZ),log_level_colour(level), log_level_text(level));
        vfprintf(stderr, format, args);
        fprintf(stderr, "%s\n", C_NRM);
        
        fflush(stderr);
    }
}

void basic_log(const char *funcname, int level, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    basic_vlog(funcname, level, format, args);
    va_end(args);
}

const char* myitoa(int num, char* buffer, int base)
{
    int curr = 0;
 
    if (num == 0)
    {
        // Base case
        buffer[curr++] = '0';
        buffer[curr] = '\0';
        return buffer;
    }
 
    int num_digits = 0;
 
    if (num < 0)
    {
        if (base == 10)
        {
            num_digits ++;
            buffer[curr] = '-';
            curr ++;
            // Make it positive and finally add the minus sign
            num *= -1;
        }
        else
        {
            // Unsupported base. Return NULL
            return NULL;
        }
    }
 
    num_digits += (int)floor(log(num) / log(base)) + 1;
 
    // Go through the digits one by one
    // from left to right
    while (curr < num_digits)
    {
        // Get the base value. For example, 10^2 = 1000, for the third digit
        int base_val = (int) pow(base, num_digits-1-curr);
 
        // Get the numerical value
        int num_val = num / base_val;
 
        char value = num_val + '0';
        buffer[curr] = value;
 
        curr ++;
        num -= base_val * num_val;
    }
    buffer[curr] = '\0';
    return buffer;
}
