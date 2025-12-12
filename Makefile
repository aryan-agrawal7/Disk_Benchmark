all:
	gcc -Wall -Wextra -o bench1 main.c Method1.c
	gcc -Wall -Wextra -o bench2 main.c Method2.c
clean:
	rm -f bench1 bench2
