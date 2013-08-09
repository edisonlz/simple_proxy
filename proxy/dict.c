#include "dict.h"

connect_fd_struct  *fds = NULL;

connect_fd_struct *hash_find(int key) {

    connect_fd_struct *s;

    HASH_FIND_INT(fds, &key, s);
    return s;
}


void hash_set(int fd,int value) {

    connect_fd_struct *s = (connect_fd_struct*) malloc(sizeof(connect_fd_struct));
    s->fd = value;
    printf("hash set %d %d\n",fd ,s->fd);
    HASH_ADD_INT( fds, fd, s );

    //connect_fd_struct *r =  hash_find(fd);
    printf("hash get %d\n",fd );

}


void hash_delete(connect_fd_struct *fd) {
    HASH_DEL( fds, fd);
    free(fd);
}

