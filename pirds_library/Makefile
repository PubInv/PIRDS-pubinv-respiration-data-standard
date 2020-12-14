all: test_PIRDS


# These shenannigans with the extension are necessary to prevent
# platformio, which automatically makes .c files, from creating
# unneeded symbol references, which in particular cause a problem
# if compiling on 8 and 32 bit architectures at the same time,
# but allow you use the tests even if you are not using platform io
test_PIRDS: Makefile test_PIRDS.c.ext PIRDS.o
	cp test_PIRDS.c.ext test_PIRDS.c
	gcc -o test_PIRDS test_PIRDS.c PIRDS.o
	rm test_PIRDS.c

PIRDS.o: Makefile PIRDS.cpp PIRDS.h
	gcc -x c -c PIRDS.cpp
