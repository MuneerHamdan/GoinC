all:
	gcc main.c board.c decisions.c -lncurses -g
	./a.out
