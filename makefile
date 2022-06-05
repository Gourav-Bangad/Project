main : main.o RBtree.o hashfunc.o
	cc -o main main.o RBtree.o hashfunc.o
main.o : main.c RBtree.c hashfunc.c hashfunc.h RBtree.h
	cc -c main.c -o main.o
hashfunc.o : RBtree.h hashfunc.c hashfunc.h RBtree.c
	cc -c hashfunc.c -o hashfunc.o
RBtree.o : RBtree.c RBtree.h 
	cc -c RBtree.c -o RBtree.o
clean:
	rm *.o
