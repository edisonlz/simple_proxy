#include <string.h>   /* memcmp,strlen */
#include <stddef.h>   /* ptrdiff_t */
#include <stdlib.h>   /* exit() */
#include <stdio.h>
#include "uthash.h"

typedef struct connect_fd {
    int c_fd; //connection file descripter
    UT_hash_handle hh; /* makes this structure hashable */
} connect_fd_struct;


connect_fd_struct *hash_find(int key);

void hash_set(int fd,int value);

void hash_delete(connect_fd_struct *fd);
