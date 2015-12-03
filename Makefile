CC = gcc
GTK_CFLAGS = -Wall -ggdb -std=c99 `pkg-config --cflags gtk+-2.0`
GSTREAMER_CFLAGS = -Wall -ggdb -std=c99 `pkg-config --cflags gstreamer-1.0`
LDFLAGS = -lm `pkg-config --libs gtk+-2.0` `pkg-config --libs gstreamer-1.0`

player : main.o player.o
	$(CC) $(LDFLAGS) -o $@ $^

main.o : main.c
	$(CC) $(GTK_CFLAGS) -o $@ -c $<

player.o: player.c
	$(CC) $(GSTREAMER_CFLAGS) -o $@ -c $< 
