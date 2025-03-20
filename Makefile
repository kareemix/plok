CC=gcc
CFLAGS=-lncurses -Wall -Wextra -pedantic

SRC_DIR=./src
BLD_DIR=./bin
REL_DIR=./rel

build: $(SRC_DIR)/main.c
	$(CC) $(SRC_DIR)/main.c -o $(BLD_DIR)/plok $(CFLAGS) -g
	echo "asdf asdf asdfasdf\nasdf asdfasdf asdf\nasdfasdf asdf asdf" > ./test/asdf

release:
	$(CC) $(SRC_DIR)/main.c -o $(REL_DIR)/plok/plok $(CFLAGS) -O2
	tar -czvf $(REL_DIR)/plok.tar.gz $(REL_DIR)/plok

cleanbin:
	rm $(BLD_DIR)/plok

cleanrel:
	rm $(REL_DIR)/plok/plok
