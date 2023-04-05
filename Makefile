CC := gcc
CFLAGS := -Wall -g -O0



all :
	gcc -g list.c list_demo.c

.PHONY: clean
clean :
	rm -rf a.out

