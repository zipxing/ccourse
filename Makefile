base: base.o
	gcc -o base base.o
base.o: base.c
	gcc -Wall -c base.c
clean:
	rm -f base.o base test.txt student.dat
