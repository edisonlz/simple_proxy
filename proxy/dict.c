#include "dict.h"

connect_fd_struct  *fds = NULL;

connect_fd_struct *hash_find(int key) {

    struct connect_fd_struct *s;

    HASH_FIND_INT(fds, &key, s);
    return s;
}


void hash_set(int fd,int value) {

    struct connect_fd_struct *s;

    HASH_FIND_INT(fds, &fd, s);  /* id already in the hash? */
    if (s==NULL) {
      s = (connect_fd_struct*) malloc(sizeof(connect_fd_struct));
      s->fd = value;
      HASH_ADD_INT( fds, fd, s );
    }

}


void hash_delete(connect_fd_struct *fd) {
    HASH_DEL( fds, fd);
    free(fd);
}

