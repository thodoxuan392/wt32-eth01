#ifndef APP_DEBUG
#define APP_DEBUG

#define MAX_LOG_BUFFER 1024

typedef enum{
    LOG_OFF,
    LOG_FATAL,
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG,
    LOG_TRACE,
    LOG_ALL
}log_level_t;

#define APPDEBUG_log_trace(...) APPDEBUG_log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define APPDEBUG_log_debug(...) APPDEBUG_log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define APPDEBUG_log_info(...)  APPDEBUG_log_log(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define APPDEBUG_log_warn(...)  APPDEBUG_log_log(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define APPDEBUG_log_error(...) APPDEBUG_log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define APPDEBUG_log_fatal(...) APPDEBUG_log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)


void APPDEBUG_init(log_level_t level);

void APPDEBUG_log_log(log_level_t level, const char *file, int line, const char *fmt, ...);


#endif // APP_DEBUG