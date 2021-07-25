CC = gcc -g
CFLAGS = -Wall -O1

DICT = dictionary
DICTPG = dictionary-pg

SFILE = shakespeare.txt
SIZE ?= 1021
HASH ?= 0
QUICK ?= 0
FIND ?= 0
LOWER ?= 0

all:

dictionary: dictionary.c options.c options.h
	$(CC) $(CFLAGS) dictionary.c options.c -o dictionary

dictionary-pg: dictionary.c options.c options.h
	$(CC) $(CFLAGS) -pg dictionary.c options.c -o dictionary-pg
	
# Build 2-gram tables of Shakespeare's works
gprof: $(DICTPG)
	./$(DICTPG) -file $(SFILE) -size $(SIZE) -hash $(HASH) -quick $(QUICK) \
		-find $(FIND) -lower $(LOWER) -verbose 1 -ngram 2
	gprof -b $(DICTPG) gmon.out
		
callgrind: $(DICT)
	valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./$(DICT) \
		-file $(SFILE) -size $(SIZE) -hash $(HASH) -quick $(QUICK) \
		-find $(FIND) -lower $(LOWER) -verbose 1 -ngram 2
	callgrind_annotate callgrind.out

clean:
	rm -f $(DICT) $(DICTPG) gmon.out callgrind.out *~

.PHONY: gprof callgrind
