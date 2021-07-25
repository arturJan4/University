CC = gcc -g -no-pie
CFLAGS = -Og -Wall
LDFLAGS = 
ASFLAGS = -g

# Configurable parameters
PROCEDURE ?= cubef.s:cubef
ILIMIT ?= 80
MAXSIZE ?= 512
BADINSNS ?= '*cnt*,call*'
MINIPC ?= 2.8

MAXINSNS = $(ILIMIT)

CHECK = ./check-solution --procedure $(PROCEDURE) \
	                 --max-size $(MAXSIZE) --bad-insns $(BADINSNS) $(EXTRA)
RUN = ./run-solution --procedure $(PROCEDURE) \
                     --max-insns $(MAXINSNS) $(EXTRA) -- ./main

all: test-random

check: main
	$(CHECK)

main: main.o cubef.o
	$(CC) $(LDFLAGS) -o $@ $^

test-1: check
	$(RUN) 0x40000000

test-2: check
	$(RUN) 0xFF800000

test-3: check
	$(RUN) 0x2A938000

test-4: check
	$(RUN) 0x8888DEAD

test-random: MAXINSNS=$(shell echo $$(($(ILIMIT)*1000))) 
test-random: check
	$(RUN) -r 1000

test-all: test-1 test-2 test-3 test-4 test-random

test-bonus: CHECK += --min-ipc $(MINIPC)
test-bonus: check

clean:
	rm -f main *.o *.out *~

.PHONY: check clean test-1 test-2 test-3 test-4 test-random test-all

# vim: ts=8 sw=8 noet
