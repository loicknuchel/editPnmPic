CC=gcc
CFLAGS= -c -W -Wall -ansi -pedantic
LDFLAGS= -lm
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
RM=rm -f
EXEC_NAME=editPnm

all: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(EXEC_NAME)
	$(RM) *.o *~ \#*\#

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	$(RM) *.o *~ \#*\#

