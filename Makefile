base: base.o multi.o
	gcc -o base base.o multi.o
base.o: base.c multi.c
	gcc -Wall -c base.c multi.c
clean:
	rm -f base.o multi.o base test.txt student.dat
