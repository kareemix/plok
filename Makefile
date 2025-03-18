build:
	gcc ./src/*.c -o ./bin/plok -lncurses -Wall -Wextra -pedantic
	echo "asdf asdf asdfasdf\nasdf asdfasdf asdf\nasdfasdf asdf asdf" > ./test/asdf
