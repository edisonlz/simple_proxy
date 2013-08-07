CC = c99
CFLAGS = -Wall -O2

proxy: clean main.c main.h
	$(CC) $(CFLAGS) -o proxy main.c network.c process.c -D_GNU_SOURCE

clean:
	rm proxy a.out -f


