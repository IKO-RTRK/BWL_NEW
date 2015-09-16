CC=gcc

all: bowling_game tests build

.PHONY: bowling_game tests build

bowling_game:
	$(CC) -c src/bowling_game.c -o ../build/bowling_game.o

tests:
	$(MAKE) -C tests all

build:
	$(MAKE) -C build all
