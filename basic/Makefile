CC = gcc
CFLAGS = -Wall

base: base.o multi.o
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f base.o multi.o base test.txt student.dat
