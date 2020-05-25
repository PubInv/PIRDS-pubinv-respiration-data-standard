all: test_PIRDS


test_PIRDS: Makefile test_PIRDS.c PIRDS.o
	gcc -o test_PIRDS test_PIRDS.c PIRDS.o

PIRDS.o: Makefile PIRDS.cpp PIRDS.h
	gcc -x c -c PIRDS.cpp
