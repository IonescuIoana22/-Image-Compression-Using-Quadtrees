# IONESCU Ioana - 312CB

build:
	gcc main.c functii.c -Wall -Werror -o quadtree
run:
	./quadtree
clean:
	rm quadtree
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./lista2