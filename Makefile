CC=gcc
CFLAGS= -g -Wall -Werror -Wextra -Wno-unused-parameter
CFLAGS+= -m32 -fno-pie -no-pie
LDFLAGS= -m32 -no-pie
EXECS=generator output1 output2
DEMO1=demo1.s
DEMO2=demo2.s

.PHONY: all clean submit

all: $(EXECS)

clean:
	rm -f *.o $(DEMO1) $(DEMO2) $(EXECS) 

output1: demo1.o main1.o
	$(CC) $(LDFLAGS) -o $@ $^

output2: demo2.o main2.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

%.o: %.s
	$(CC) $(CFLAGS) -c $<

$(DEMO1): generator demo1.txt
	./$< demo1.txt

$(DEMO2): generator demo2.txt
	./$< demo2.txt

generator: generator.o stack.o
	$(CC) $(LDFLAGS) -o $@ $^

generator.o: generator.c stack.h
	$(CC) $(CFLAGS) -c $<
