#include "main.h"
#include "network.h"
#include "process.h"

/* for select */
#include <sys/select.h>


void io_loop(int listen_sock, int epoll_fd) {

    int nfds;
    uint32_t events;
    struct epoll_event epoll_events[MAX_EVENTS];
    
    while(1) {
    
        nfds = epoll_wait(epoll_fd, epoll_events, MAX_EVENTS, -1);

        for (int i = 0; i < nfds; ++ i) {
            events = epoll_events[i].events;
            if (epoll_events[i].data.fd == listen_sock) {
                
                accept_incoming(listen_sock, epoll_fd);

            }  else {

                if ((events & EPOLLERR)) {
                        #ifdef DEBUG
                           printf("error condiction, events: %d, fd: %d\n", events, epoll_fd);
                        #endif
                    
                        close_and_clean(epoll_events[i].data.fd);
                    
                } else {
                    if (events & EPOLLIN) {

                        printf("process request, sock_fd %d\n", epoll_fd);
                        process_request(epoll_events[i].data.fd, epoll_fd, &epoll_events[i]);
                        
                    }
                    
                    if (events & EPOLLOUT) {
                         printf("EPOLLOUT sock_fd: %d write\n",epoll_fd);
                    }
                }
            }
        }
    }
}




int connect_remote(char *server,int port){

    int remote = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sin;
    
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    inet_pton(AF_INET,server,&sin.sin_addr);
    
    if (connect(remote, (struct sockaddr*) &sin, sizeof(sin))) {
        perror("connect remote");
        close(remote);
        return 1;
    }

    make_socket_non_blocking(remote);

    return remote;
}

void add_proxy_epoll_event(int client,int remote,int epollfd){

    struct epoll_event ev;

    pair_epoll_data data;
    data.pair_fd = client;
    ev.data.ptr = &data;
    
    ev.events = EPOLLIN ; //| EPOLLOUT;  | EPOLLET; //  read, edge triggered
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, remote, &ev) == -1) {
        perror("remote proxy add event");
        exit(EXIT_FAILURE);
    }
    
}


void process_request(int client, int epoll_fd, struct epoll_event* ev) {

    ssize_t count;

    printf("on !ev->data.ptr\n");
    
    if(!ev->data.ptr){

        printf("!ev->data.ptr\n");

        /* proxy to server*/
        
        char buf[64];
        count = read_all(client, buf);

        printf("read_all\n");
        
        const char * split = ":";

        char *server;
        int port;

        char * p;
        p = strtok (buf, split);
        server = p;
        p = strtok(NULL, split);
        port = atoi(p);

        printf("server:%s,port:%d\n",server,port);

        /*1. connect to remote server*/
        int remote = connect_remote(server, port);

        /*2. client event register remote info*/
        pair_epoll_data data;
        data.pair_fd = remote;
        ev->data.ptr = &data;

        printf("register %d %d" , client , remote);
        /*3. remote add to epoll */
        add_proxy_epoll_event(client, remote , epoll_fd);

    }else{
        /*
           1. client read to porxy
           2. proxy read to client
        */
        char buf[4096];
        count = read_all(client, buf);
        pair_epoll_data * data = (pair_epoll_data *) ev->data.ptr;
        printf("send all to %d" , data->pair_fd);
        send_all(data->pair_fd , buf);
    }
}




int main(int argc, char** argv) {

    //1.listen socket on port
    int listen_sock = open_non_blocking_socket(30000);

    //2.fork load balance server
    fork_processes(2);

    //3. create epoll and register event
    int epoll_fd = epoll_start(listen_sock);

    //4.io loop for waiting network events.
    io_loop(listen_sock, epoll_fd);

    //no coming
    return 0;
}

