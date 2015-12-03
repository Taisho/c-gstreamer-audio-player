#define SLIDER_LENGTH 300

enum{
  COLUMN_TRACKNUMBER,
  COLUMN_ARTIST,
  COLUMN_TITLE,
  COLUMN_ALBUM,
  COLUMN_LENGTH,
  NUM_COLUMNS
};

typedef struct {
  int tracknumber;
  gchar * artist;
  gchar *title;
  gchar *album;
  gchar *length;
  gchar *filename;
} Playlist_t;
