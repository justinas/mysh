CFLAGS = -g -Wall -std=gnu99
LDFLAGS = -L/usr/local/lib -I/usr/local/include -lreadline

mysh: builtins.o bytebuf.o command.o exec.o main.o token.o
	$(CC) -o mysh $^ $(LDFLAGS)

clean:
	rm -f *.o mysh
.PHONY: clean
