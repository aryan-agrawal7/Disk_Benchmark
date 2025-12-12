all:
	gcc -Wall -Wextra -o bench1 src/main.c src/Method1.c
	gcc -Wall -Wextra -o bench2 src/main.c src/Method2.c
clean:
	rm -f bench1 bench2
