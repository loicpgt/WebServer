#include <stdio.h>
#include <stdlib.h>

#include "log/log.h"
#include "web/server.h"


int main(int argc, char const *argv[])
{
    struct web_server* server = web_server_construct(DEFAULT_BACKLOG);
    int runResult = web_server_run(server, DEFAULT_PORT);

    web_server_destruct(server);
    free(server);

    return 0;
}
