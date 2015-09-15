CC=gcc

all: gui tests build

.PHONY: gui tests build

gui:
	$(CC) -c src/gui.c -o ../build/gui.o

tests:
	$(MAKE) -C tests all

build:
	$(MAKE) -C build all
