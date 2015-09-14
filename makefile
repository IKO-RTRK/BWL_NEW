all: bowling_game player ball gui main build

.PHONY: bowling_game player ball gui main build

bowling_game:
	$(MAKE) -C stats all

player:
	$(MAKE) -C player all

ball:
	$(MAKE) -C ball_logic all

gui:
	$(MAKE) -C gui all

main:
	$(MAKE) -C main all

build:
	$(MAKE) -C build all

