CC = gcc
CFLAGS = -Wall
OBJS = base.o multi.o

base: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f $(OBJS) base test.txt student.dat
