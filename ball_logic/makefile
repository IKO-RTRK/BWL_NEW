CC=gcc

all: ball tests build

.PHONY: ball tests build

ball:
	$(CC) -c src/ball.c -o ../build/ball.o

tests:
	$(MAKE) -C tests all

build:
	$(MAKE) -C build all
