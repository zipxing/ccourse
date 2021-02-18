CC = gcc
CFLAGS = -Wall `pkg-config --libs --cflags raylib`

wave: wave.c
	$(CC) $(CFLAGS) -o $@ $^
snake: snake.c
	$(CC) $(CFLAGS) -o $@ $^
luoxuan: luoxuangui.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f $(OBJS) wave snake luoxuan
