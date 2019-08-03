# mysh

A very barebones shell.

## Here be dragons

It's just not a very good shell. You don't really want to use it.

## Usage

Probably linux-only because of `linux/limits.h` include.
Depends on libreadline.

```
$ make
$ ./mysh
```

## Features

* Builtins: `cd`, `echo`, `exit`
* Command execution
* Stdin/stdout/stderr redirection
* A non-persistent history (CTRL-R, etc.), thanks to readline
