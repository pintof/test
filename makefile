CC=gcc
CFLAGS= -Wall -pedantic -std=c99

runMe:
	$(CC) $(CFLAGS) q1.c -o q1
	$(CC) $(CFLAGS) q2.c -o q2