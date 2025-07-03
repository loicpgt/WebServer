#include <stdio.h>
#include "log/log.h"

int main(int argc, char const *argv[])
{
    LOG_INFO("Without parameters");
    LOG_INFO("With parameters: %1.2f", 1.247);
    LOG_WARNING("Warning log");
    LOG_ERROR("Error log");
    printf("Hello World!\n");
    return 0;
}
