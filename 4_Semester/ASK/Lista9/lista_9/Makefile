CC = gcc -g
CFLAGS = -Og -Wall

FILES = relo3.o lazy ropex ropex.in

all: $(FILES)

%.o: %.c
	$(CC) $(CFLAGS.$*) $(CFLAGS) -c -o $@ $^

%.s: %.c
	$(CC) $(CFLAGS.$*) $(CFLAGS) -S -o $@ $^

ropex: CC += -static
ropex: CFLAGS += -fno-pie -fno-stack-protector -fno-asynchronous-unwind-tables 
ropex: ropex.o ropex.o gadget.o
	$(CC) $(CFLAGS) -Wl,-Map=$@.map -o $@ $^

ropex.in: ropex.in.txt
	# requires `xxd` package to be installed
	xxd -r $^ >$@

lazy: lazy.c
	gcc -Os -Wall -ggdb -o $@ $^

clean:
	rm -f *.o *.map *~
	rm -f $(FILES)

# vim: ts=8 sw=8 noet
