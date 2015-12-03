#include <glib-object.h>
#include "types.h"

/* This program creates a tree view
 * and modifies a particular row
 */

extern void do_gstreamer_player();
extern void seek_in_seconds(gdouble);
extern gdouble stream_length;

gdouble fill_level;

Playlist_t data[]=
{
  {1, "Adress on web", "Adress on web", "Radio 161fm", "00:00", "file:///home/tichomir/Music-Collection/Radio161-2014-95-21/003.Adress on web.ogg"},
  {2, "Hot Natured Feat. Roisin Murphy", "Alternate State", "Radio 161fm", "00:00", "file:///home/tichomir/Music-Collection/Radio161-2014-95-21/004.Hot Natured Feat. Roisin Murphy - Alternate State.ogg"},
};

int main (int argc, char **argv){
  /* Run the play back */
  do_gstreamer_player();
  gtk_main();
  return 0;
} 
