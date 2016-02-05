#include <stdlib.h>
#include <string.h>
#include "playlist.h"

/*

typedef struct {
  int tracknumber;
  gchar * artist;
  gchar *title;
  gchar *album;
  gchar *length;
  gchar filename[PATH_LENGTH];
  //int nPlayCount // if it is larger by 0, it can be deleted, as this is a queue.
} TrackEntry_t;//FIXED rename to TrackEntry_t

typedef struct {
    
    int nTracks;
    int iCurrentTrack;
    TrackEntry_t * track;
} Playlist_t;
*/


Playlist_t * playlistNew(int nEntries)
{
    char * playlistPool = malloc(sizeof(TrackEntry_t)*nEntries
				+ sizeof(Playlist_t));
    if (playlistPool == NULL)
    {
	return NULL;
    }

    Playlist_t * playlist = (Playlist_t*) playlistPool;

    playlist->capacity = nEntries;
    playlist->nTracks = 0;
    playlist->iCurrentTrack = 0;
    playlist->track = (TrackEntry_t*) &playlistPool[sizeof(Playlist_t)];

    return playlist;
}

void playlistDestroy(Playlist_t * playlist)
{
    free(playlist);
}

int playlistNextTrack(Playlist_t * playlist)
{
    /* Playlist is empty */
    if(playlist->nTracks == 0)
    {
	return 0;
    }

    if(playlist->iCurrentTrack+1 < playlist->nTracks)
    {
	playlist->iCurrentTrack++;
	return 1;
    }
    else
    {
	return 0;
    }
}

int playlistPreviousTrack(Playlist_t * playlist)
{
    /* Playlist is empty */
    if(playlist->nTracks == 0)
    {
	return 0;
    }

    if(playlist->iCurrentTrack-1 >= 0 )
    {
	playlist->iCurrentTrack--;
	return 1;
    }
    else
    {
	return 0;
    }
}

char * playlistGetCurrentFileName(Playlist_t * playlist)
{
    /* Playlist is empty */
    if(playlist->nTracks == 0)
    {
	return 0;
    }

    TrackEntry_t * track = playlist->track;
    char * fileName = track[playlist->iCurrentTrack].fileName;

    return fileName;
}

int playlistAppendFileName(Playlist_t * playlist, char * fileName)
{
    /* Playlist is full */
    if(playlist->nTracks + 1 > playlist->capacity)
    {
	return 0;
    }

    TrackEntry_t * newEntry = &playlist->track[playlist->nTracks];
    playlist->nTracks++;

    strcpy(&(newEntry->fileName), fileName);

    return 1;
}

int playlistIsEmpty(Playlist_t * playlist)
{
    if(playlist->nTracks == 0)
    {
        return 1;
    }
    else
    {
	return 0;
    }
}

int playlistIsFull(Playlist_t * playlist)
{
    if(playlist->nTracks >= playlist->capacity)
    {
        return 1;
    }
    else
    {
	return 0;
    }
}

//void playlistTraverse(callback(int 
