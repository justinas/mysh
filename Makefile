CFLAGS = -g -Wall -std=gnu99

mysh: builtins.o bytebuf.o command.o exec.o main.o token.o
	$(CC) -o mysh $^

clean:
	rm -f *.o mysh
.PHONY: clean
