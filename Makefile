CC=gcc
CFLAGS= -g -Wall -Werror -Wextra -Wno-unused-parameter
CFLAGS+= -m32 -fno-pie -no-pie
LDFLAGS= -m32 -no-pie
EXECS=generator output1 output2

.PHONY: all clean 

all: $(EXECS)

clean:
	rm -f *.o *.s $(EXECS) 

output1: demo1.o main1.o
	$(CC) $(LDFLAGS) -o $@ $^

output2: demo2.o main2.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

%.o: %.s
	$(CC) $(CFLAGS) -c $<

%.s: generator %.txt
	./$^

generator: generator.o stack.o
	$(CC) $(LDFLAGS) -o $@ $^

generator.o: generator.c stack.h stack.c
	$(CC) $(CFLAGS) -c $<
