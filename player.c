#include <stdio.h>
#include <glib.h>
#include <gst/gst.h>
#include "player.h"

//extern void set_slider_value(gdouble);

GstElement* pipeline;
GstBus *bus;
guint bus_watch_id;
//guint playlist_index=0;
gdouble stream_length;
Playlist_t * mainQueue;

static gboolean
bus_call (GstBus     *bus,
          GstMessage *msg,
          gpointer    data)
{
  GMainLoop *loop = (GMainLoop *) data;

  switch (GST_MESSAGE_TYPE (msg)) {

    case GST_MESSAGE_EOS:
      g_print ("End of stream\n");
      //starting next song
      //g_object_set (G_OBJECT (source), "location", second_file, NULL);
      //gst_element_set_state (pipeline, GST_STATE_PLAYING);
      g_main_loop_quit (loop);
      break;

    case GST_MESSAGE_ERROR: {
      gchar  *debug;
      GError *error;

      gst_message_parse_error (msg, &error, &debug);
      g_free (debug);

      g_printerr ("Error: %s\n", error->message);
      g_error_free (error);

      g_main_loop_quit (loop);
      break;
    }
    default:
      break;
  }

  return TRUE;
}

void next_track(GstElement *playbin, gpointer userdata){
    //if(trackIndex+1 <= playlist.nTracks)
  //playlist_index++;

    if(playlistNextTrack(mainQueue))
    {
	g_object_set(G_OBJECT(playbin), "uri", playlistGetCurrentFileName(mainQueue) , NULL);
	g_print ("Now playing: %s\n", playlistGetCurrentFileName(mainQueue));
    }
}

void seek_in_seconds(gdouble seconds){
  gst_element_seek (pipeline, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
		    GST_SEEK_TYPE_SET, seconds * GST_SECOND,
		    GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE);
  printf("%f\n", seconds);
}

/*
static gboolean
cb_print_position (){
  gint64 pos, len;
  gdouble new_position_in_slider;
  gdouble position_in_seconds;

  if (gst_element_query_position (pipeline, GST_FORMAT_TIME, &pos)
      && gst_element_query_duration (pipeline, GST_FORMAT_TIME, &len))
    {
      stream_length = len / 1000000000;
      position_in_seconds = (pos/1000000000.0);
      new_position_in_slider = position_in_seconds*(SLIDER_LENGTH / stream_length);

      //set_slider_value(new_position_in_slider);
    }
} */
void runPlayback(gpointer userdata){

    //TODO get GST_STATE
    GstState state;
    gst_element_get_state(pipeline, &state, NULL, GST_CLOCK_TIME_NONE);

    if(state == GST_STATE_READY || state == GST_STATE_PAUSED){ 

	//FIXME This is not how to play the next track. Google
	g_object_set (G_OBJECT (pipeline), "uri", playlistGetCurrentFileName(mainQueue), NULL);
	gst_element_set_state (pipeline, GST_STATE_PLAYING);
    }

}

void playbackToggle(gpointer userdata){

    //TODO get GST_STATE
    GstState state;
    gst_element_get_state(pipeline, &state, NULL, GST_CLOCK_TIME_NONE);

    if(state == GST_STATE_PLAYING ){ 

	gst_element_set_state (pipeline, GST_STATE_PAUSED);
    }
    else{

	//g_object_set (G_OBJECT (pipeline), "uri", playlistGetCurrentFileName(mainQueue), NULL);
	gst_element_set_state (pipeline, GST_STATE_PLAYING);
    }

}
void do_gstreamer_player(){

  gst_init (NULL, NULL);
  /* Create gstreamer elements */
  pipeline = gst_element_factory_make ("playbin", NULL);

  if (!pipeline) {
    g_printerr ("The playbin couldn't be created. Exiting.\n");
    return;
  }

  /* Set up the pipeline */

  /* When a song is about to finish, our handler prepares the next track */
  g_signal_connect(G_OBJECT(pipeline), "about-to-finish",
		   G_CALLBACK(next_track), NULL);

  g_signal_connect(G_OBJECT(pipeline), "playlist-updated",
		   G_CALLBACK(runPlayback), NULL);

  g_signal_connect(G_OBJECT(pipeline), "playback-next",
		   G_CALLBACK(next_track), NULL);

  g_signal_connect(G_OBJECT(pipeline), "playback-toggle",
		   G_CALLBACK(playbackToggle), NULL);

    //FIXME at startup the MainQueue should be empty!
  /* we set the input filename to the source element */
  //g_object_set (G_OBJECT (pipeline), "uri", data[0].filename, NULL);

  /* we add a message handler */
  bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  bus_watch_id = gst_bus_add_watch (bus, bus_call, NULL);
  gst_object_unref (bus);

    //FIXME start in Paused state!
  /* Set the pipeline to "playing" state*/

/*  g_print ("Now playing: %s\n", data[0].filename);
  g_object_set (G_OBJECT (pipeline), "uri", data[0].filename, NULL);
  gst_element_set_state (pipeline, GST_STATE_PLAYING);
*/
  //g_print ("Running...\n");
  //g_timeout_add(250, (GSourceFunc) cb_print_position, NULL);

}
