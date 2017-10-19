CFLAGS = -g -Wall -std=c99

mysh: bytebuf.o main.o token.o
	$(CC) -o mysh $^

clean:
	rm -f *.o mysh
.PHONY: clean
