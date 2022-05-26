main: main.o skiplist.o
	gcc -o main main.o skiplist.o
main.o: main.c skiplist.c skiplist.h
	gcc -c main.c -o main.o
skiplist.o: skiplist.c skiplist.h
	gcc -c skiplist.c -o skiplist.o
clean:
	rm *.o