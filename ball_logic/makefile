all: ball test player stats build

.PHONY:	ball test player build

ball:
	gcc -c src/ball.c -o ../build/ball.o

test:
	$(MAKE) -C tests all

player:
	cd ../ && $(MAKE) -C player all

stats:
	cd ../ && $(MAKE) -C stats all

build:
	$(MAKE) -C build all