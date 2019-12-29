#компилятор
CC = gcc
RM = rm
CFLAGS = -std=c99 -Wall -Werror -ggdb

##описание для основной программы
app.exe: main.o analysis.o array_stack.o list_stack.o parentheses.o
	$(CC) -o app.exe main.o analysis.o array_stack.o list_stack.o parentheses.o
main.o: main.c analysis.h array_stack.h list_stack.h parentheses.h
	$(CC) $(CFLAGS) -c main.c
analysis.o: analysis.c analysis.h array_stack.h list_stack.h 
	$(CC) $(CFLAGS) -c analysis.c
array_stack.o: array_stack.c array_stack.h
	$(CC) $(CFLAGS) -c array_stack.c
list_stack.o: list_stack.c list_stack.h
	$(CC) $(CFLAGS) -c list_stack.c
parentheses.o: parentheses.c parentheses.h list_stack.h
	$(CC) $(CFLAGS) -c parentheses.c
##описание для удаления 
clean:
	$(RM) *.o *.exe