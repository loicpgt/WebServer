#include <stdio.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG_INFO(fmt, ...) \
    fprintf(stdout, "[\x1b[32mINFO\x1b[0m]    %s:%d " fmt "\n", __FILENAME__,__LINE__, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) \
    fprintf(stdout, "[\x1b[33mWARNING\x1b[0m] %s:%d " fmt "\n", __FILENAME__,__LINE__, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) \
    fprintf(stderr, "[\x1b[31mERROR\x1b[0m]   %s:%d " fmt "\n", __FILENAME__,__LINE__, ##__VA_ARGS__)
