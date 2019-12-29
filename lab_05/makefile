CC = gcc
CFLAGS = -std=c99 -Wall -Werror
RM =rm

app.exe: main.o action.o quearr.o quelist.o
	$(CC) -o app.exe main.o action.o quearr.o quelist.o
main.o: main.c action.h quearr.h quelist.h
	$(CC) $(CFLAGS) -c main.c
action.o: action.c action.h 
	$(CC) $(CFLAGS) -c action.c
quearr.o: quearr.c quearr.h
	$(CC) $(CFLAGS) -c quearr.c
quelist.o: quelist.c quelist.h
	$(CC) $(CFLAGS) -c quelist.c

clean:
	$(RM) *.o*.exe