#ifndef PLAYER_H
#define PLAYER_H

#include "playlist.h"

//#define SLIDER_LENGTH 300
//#define TRACK_LIST_SIZE 10

enum{
  COLUMN_TRACKNUMBER,
  COLUMN_ARTIST,
  COLUMN_TITLE,
  COLUMN_ALBUM,
  COLUMN_LENGTH,
  NUM_COLUMNS
};

//extern void set_slider_value(gdouble);
extern void do_gstreamer_player();
//extern void seek_in_seconds(gdouble);

//extern gdouble stream_length;
extern Playlist_t * mainQueue;

#endif
