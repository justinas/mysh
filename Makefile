CFLAGS = -Wall -std=c99

mysh: bytebuf.o main.o
	$(CC) -o mysh $^

clean:
	rm -f *.o mysh
.PHONY: clean
