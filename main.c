#include <glib-object.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include "player.h"
#include "server.h"

//gdouble fill_level;

pthread_t server_thread;


int main (int argc, char **argv){

    /* Register new signal */
    g_signal_new("playlist-updated",
             G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
             0, NULL, NULL,
             g_cclosure_marshal_VOID__POINTER,
             G_TYPE_NONE, 1, G_TYPE_POINTER);

    g_signal_new("playback-next",
             G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
             0, NULL, NULL,
             g_cclosure_marshal_VOID__POINTER,
             G_TYPE_NONE, 1, G_TYPE_POINTER);

    g_signal_new("playback-toggle",
             G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
             0, NULL, NULL,
             g_cclosure_marshal_VOID__POINTER,
             G_TYPE_NONE, 1, G_TYPE_POINTER);


    /* Allocate MainQueue */
    mainQueue = playlistNew(10); //10 entries

    printf("cap: %i\nnTr: %i\n", mainQueue->capacity, mainQueue->nTracks);

    /* Run server */
    pthread_create(&server_thread, NULL, do_server, NULL);

    /* Run the play back */
    do_gstreamer_player();
    gtk_main();
    return 0;
} 
