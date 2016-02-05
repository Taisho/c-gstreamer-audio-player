#ifndef PLAYLIST_H
#define PLAYLIST_H

#ifndef NULL
#define NULL 0
#endif

//do not change PATH_LENGTH, unless you port the code to another system !
#define PATH_LENGTH 4096+1

typedef struct {
  int tracknumber;
  char * artist;
  char *title;
  char *album;
  char *length;
  char fileName[PATH_LENGTH];
  //int nPlayCount // if it is larger by 0, it can be deleted, as this is a queue.
} TrackEntry_t;//FIXED rename to TrackEntry_t

typedef struct {
    int capacity;
    int nTracks;
    int iCurrentTrack;
    TrackEntry_t * track;
} Playlist_t;

Playlist_t * playlistNew(int nEntries);
void playlistDestroy(Playlist_t * playlist);
char * playlistGetCurrentFileName(Playlist_t * playlist);
int playlistAppendFileName(Playlist_t * playlist, char * fileName);
int playlistIsEmpty(Playlist_t * playlist);
int playlistIsFull(Playlist_t * playlist);

//TODO document these functions
int playlistNextTrack(Playlist_t * playlist);
int playlistPreviousTrack(Playlist_t * playlist);
#endif
