CFLAGS=-Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

all: list dispatcher listener

list: list.c list.h
	gcc $(CFLAGS) -c list.c -o list.o

dispatcher: dispatcher.c list.o
	gcc $(CFLAGS) list.o dispatcher.c -o dispatcher

listener: listener.c relay.h 
	gcc $(CFLAGS) listener.c -o listener

debug: CFLAGS += -DDEBUG -g
debug: all

profile: CFLAGS += -pg
profile: all

clean:
	rm -f list.o dispatcher listener
