#include "dict.h"

connect_fd_struct  *fds = NULL;

connect_fd_struct *hash_find(int key) {

    connect_fd_struct *s;

    HASH_FIND_INT(fds, &key, s);
    return s;
}


void hash_set(int fd,int value) {

    connect_fd_struct *s = (connect_fd_struct*) malloc(sizeof(connect_fd_struct));
    //strcpy(s->pair_fd , value);
    s->pair_fd = value;
    HASH_ADD_INT( fds, fd, s );

}


void hash_delete(connect_fd_struct *fd) {
    HASH_DEL( fds, fd);
    free(fd);
}

