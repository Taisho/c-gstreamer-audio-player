CC = gcc
GTK_CFLAGS = -Wall -ggdb -std=c99 `pkg-config --cflags gtk+-2.0`
GSTREAMER_CFLAGS = -Wall -ggdb -std=c99 `pkg-config --cflags gstreamer-1.0`
LDFLAGS = -pthread -lm `pkg-config --libs gtk+-2.0` `pkg-config --libs gstreamer-1.0`

player : main.o player.o server.o queue.o playlist.o
	$(CC) $(LDFLAGS) -o $@ $^

queue.o : queue.c
	$(CC) -o $@ -c $<

server.o : server.c 
	$(CC) -o $@ -c $<

main.o : main.c
	$(CC) $(GTK_CFLAGS) -pthread -o $@ -c $<

player.o: player.c
	$(CC) $(GSTREAMER_CFLAGS) -o $@ -c $< 

playlist.o : playlist.c
	$(CC) -o $@ -c $<
