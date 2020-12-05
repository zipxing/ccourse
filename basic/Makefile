base: base.o multi.o
	gcc -o base base.o multi.o
base.o: base.c 
	gcc -Wall -c base.c
multi.o: multi.c
	gcc -Wall -c multi.c
clean:
	rm -f base.o multi.o base test.txt student.dat
