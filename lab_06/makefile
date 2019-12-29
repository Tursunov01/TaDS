CC = gcc
CFLAGS = -std=c99 -Wall -Wall -ggdb
RM = rm

app.exe: main.o hash.o tree.o efficiency.o
	$(CC) -o app.exe main.o hash.o tree.o efficiency.o
main.o: efficiency.h tree.h constants.h hash.h
	$(CC) $(CFLAGS) -c main.c
hash.o: hash.h constants.h tree.h
	$(CC) $(CFLAGS) -c hash.c
tree.o: tree.h constants.h
	$(CC) $(CFLAGS) -c tree.c
efficiency.o: efficiency.h tree.h constants.h hash.h
	$(CC) $(CFLAGS) -c efficiency.c

clean:
	$(RM) *.o *.exe *.gv