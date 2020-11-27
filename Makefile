base: base.o
	gcc -o base base.o
base.o: base.c
	gcc -c base.c
clean:
	rm -f base.o base
