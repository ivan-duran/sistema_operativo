.PHONY: all main words_menu

all: main words_menu

main:
	$(MAKE) -C main

words_menu:
	$(MAKE) -C words_menu
