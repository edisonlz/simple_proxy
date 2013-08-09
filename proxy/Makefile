CC = c99
CFLAGS = -Wall -O2

proxy: clean main.c main.h uthash.h network.h network.c process.h process.c dict.h dict.c
	$(CC) $(CFLAGS) -o proxy main.c network.c process.c dict.c  -D_GNU_SOURCE

clean:
	rm proxy a.out -f


