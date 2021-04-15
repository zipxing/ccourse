CC = g++
CFLAGS = -Wall `pkg-config --libs --cflags raylib` --std=c++11

game: game.cc init.cc update.cc render.cc
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f $(OBJS) game
