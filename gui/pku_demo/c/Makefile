CC = gcc
CFLAGS = -Wall `pkg-config --libs --cflags raylib`

game: game.c data.c init.c update.c render.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f $(OBJS) game
