/*
 * This file contains data structures related to playlist, namely Playlist_t and TrackEntry_t.
 * A Playlist_t can have an arbitrary number of TrackEntry_t's as compozed OO.
 *
 * @Included by playlist.c
 *
 */

#ifndef PLAYLIST_H
#define PLAYLIST_H

#ifndef NULL
#define NULL 0
#endif

#include <glib-object.h>

G_BEGIN_DECLS

//do not change PATH_LENGTH, unless you port the code to another system !
#define PATH_LENGTH 4096+1

//typedef struct {
//    int trackNumber;
//    int deckNumber;
//    char * artist;
//    char *title;
//    char *album;
//    //char *length;
//    //The following two are used for bookmarks
//    int lengthSeconds;
//    int offsetSeconds;
//    char fileName[PATH_LENGTH];
//    //int nPlayCount // if it is larger by 0, it can be deleted, as this is a queue.
//} TrackEntry_t;//FIXED rename to TrackEntry_t
//
//typedef struct {
//    int decks; // number of decks
//    int capacity;
//    int nTracks;
//    int iCurrentTrack;
//    TrackEntry_t * track;
//} Playlist_t;

#define TYPE_PLAYLIST (playlist_get_type())

typedef struct _PlaylistClass {
    GObjectClass parent_class;
} PlaylistClass;

typedef struct _Playlist {
    GObject parent_instance;
} Playlist;


GType playlist_get_type(void);
Playlist* playlist_new(void);

// WARNING playlistNew() deprecated. Use g_object_new(Playlist) instead
//Playlist_t * playlistNew(int nEntries);
//// WARNING Deprecated
//void playlistDestroy(Playlist_t * playlist);
//
//void playlistFromFile(char * filename);
//void playlistToFile(char * filename);
//char * playlistGetCurrentFileName(Playlist_t * playlist);
//int playlistAppendFileName(Playlist_t * playlist, char * fileName);
//int playlistIsEmpty(Playlist_t * playlist);
//int playlistIsFull(Playlist_t * playlist);
//
////TODO document these functions
//int playlistNextTrack(Playlist_t * playlist);
//int playlistPreviousTrack(Playlist_t * playlist);
#endif
