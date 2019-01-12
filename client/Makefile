CC = gcc
GTK_CFLAGS = -Wall -ggdb -std=c99 `pkg-config --cflags gtk+-2.0` `pkg-config --cflags glib-2.0`
GSTREAMER_CFLAGS = -Wall -ggdb -std=c99 `pkg-config --cflags gstreamer-1.0`
LDFLAGS = -pthread -lm `pkg-config --libs gtk+-2.0` `pkg-config --libs glib-2.0` `pkg-config --libs gstreamer-1.0`

client: client.o
	$(CC) $(LDFLAGS) -o $@ $^

client.o: client.c
	$(CC) $(GTK_CFLAGS) -pthread -o $@ -c $<
