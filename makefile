main: main.o RBtree.o
	gcc -o main main.o RBtree.o
main.o: main.c RBtree.c RBtree.h
	gcc -c main.c -o main.o
RBtree.o: RBtree.c RBtree.h
	gcc -c RBtree.c -o RBtree.o
clean:
	rm *.o