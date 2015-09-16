CC=gcc

all: player tests build
.PHONY: player tests build

player:
	$(CC) -c src/player.c -o ../build/player.o
tests:
	$(MAKE) -C tests all
build:
	$(MAKE) -C build all
