CC = gcc
CFLAGS = -Wall `pkg-config --libs --cflags glib-2.0`

ga: garray.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f $(OBJS) ga
