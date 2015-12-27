CFLAGS=-std=c++11
#CFLAGS=-std=c++11
CFLAGS+=-stdlib=libc++
CFLAGS+=-lncurses
#flags for test.c
CC=clang++
DEBUG=-g
#warnings
WARNINGS=-Weverything
#always have -Weverything on for SO lol
OPT= -O0 -O1 -O2 -O3 -O4

%: %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(DEBUG)

ioTest: io.o
	$(CC) io.o ioTest.cpp $(CFLAGS) -o $@ $(DEBUG)
