CC = gcc
CFLAGS = -std=c99 -Wall -Werror -ggdb
RM = rm

app.exe: main.o io.o task.o
	$(CC) -o app.exe main.o io.o task.o
main.o: head.h
	$(CC) $(CFLAGS) -c main.c
io.o: head.h
	$(CC) $(CFLAGS) -c io.c
task.o: head.h
	$(CC) $(CFLAGS) -c task.c

clean:
	$(RM) *.exe *.o