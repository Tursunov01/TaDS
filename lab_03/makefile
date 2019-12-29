%.o : %.c *.h
	gcc -c $< -std=c99 -g3
app.exe: main.o alloc.o input.o matrices.o output.o time_testing.o
	gcc -o app.exe main.o alloc.o input.o matrices.o output.o time_testing.o
clean:
	rm *.o *.exe