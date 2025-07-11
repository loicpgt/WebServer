/* DEFAULT CONFIGURATION */
#define DEFAULT_PORT 80 
#define DEFAULT_BACKLOG 10

typedef struct web_server;

struct web_server* web_server_construct(short const backlogSize);
void web_server_destruct(struct web_server* this);

/*
 * Starts to listen on the given port
 * Returns 0 if the server behaved and then left succesfully
 * Returns 1 if an error occurred
 */
int web_server_run(struct web_server* const this, short const port);
