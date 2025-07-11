#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "server.h"
#include "../log/log.h"

typedef struct web_server
{
    short backlogSize;
};

struct web_server* web_server_construct(short const backlogSize)
{
    struct web_server* server = (struct web_server*)malloc(sizeof(struct web_server));
    server->backlogSize = backlogSize;
    return server;
}

void web_server_destruct(struct web_server *this)
{
    return;
}

int __create_socket_fd(struct web_server* this, struct sockaddr_in* const host)
{
    int socket_fd = socket(host->sin_family, SOCK_STREAM, 0);
    if(socket_fd == -1) {
        LOG_ERROR("An error occured while creating the socket: %s", strerror(errno));
        return -1;
    }

    int status = bind(socket_fd, (struct sockaddr *)host, sizeof(*host));
    if(status != 0) {
        LOG_ERROR("An error occured while binding the socket %d: %s", socket_fd, strerror(errno));
        return -1;
    }

    return socket_fd;
}

int web_server_run(struct web_server *const this, short const port)
{
    struct sockaddr_in sa;
    int socket_fd;
    int client_fd;
    int status;
    struct sockaddr_storage client_addr;
    socklen_t addr_size;
    addr_size = sizeof(client_addr);
    char buffer[BUFSIZ];
    int bytes_read;

    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    sa.sin_port = htons(port);

    while(1) {
        socket_fd = __create_socket_fd(this, &sa);
        if(socket_fd == -1)
        {
            return 1;
        }
        listen(socket_fd, this->backlogSize);

        LOG_INFO("Waiting for request to be received..");

        client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &addr_size);
        LOG_INFO("New connexion received on client socket fd %d", client_fd);

        bytes_read = 1;
        while(bytes_read >= 0) {
            bytes_read = recv(client_fd, buffer, BUFSIZ, 0);
            if(bytes_read == 0) {
                break;
            }
            else if(bytes_read == -1) {
                LOG_ERROR("An error occured reading the client data: %s", strerror(errno));
                return 1;
            }
            else {
                char* msg = "Got your msg";
                int msg_len = strlen(msg);
                int bytes_sent;

                buffer[bytes_read] = "\0";
                bytes_sent = send(client_fd, msg, msg_len, 0);
                if (bytes_sent == -1) {
                    LOG_ERROR("An error occured sending the response: %s", strerror(errno));
                    return 1;
                }
            }
        }

        close(client_fd);
        close(socket_fd);
    }

    return 0;
}
