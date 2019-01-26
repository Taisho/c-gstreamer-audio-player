#include <gtk/gtk.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SLIDER_LENGTH 300
#include "../playlist.h"

GtkWidget* mainwin = NULL;
GtkTreeModel* model = NULL;

char *socket_path = "\0hidden";
int socket_fd; //socket file descriptor

enum { 
  COLUMN_ORDINAL,
  COLUMN_TYPE,
  COLUMN_ARTIST,
  COLUMN_TITLE,
  COLUMN_NAME,
  COLUMN_ALBUM,
  COLUMN_LENGTH,
  COLUMN_STARTTIME,
  NUM_COLUMNS
};

static GtkTreeModel *
create_model (void)
{
  gint i = 0;
  GtkListStore *store;
  GtkTreeIter iter;

  /* create list store */
  store = gtk_list_store_new (NUM_COLUMNS,
			      G_TYPE_INT,
                              G_TYPE_STRING,
                              G_TYPE_STRING,
                              G_TYPE_STRING,
                              G_TYPE_STRING);

  /* add data to the list store */
//  for (i = 0; i < 4; i++)
//    {
//      gtk_list_store_append (store, &iter);
//      gtk_list_store_set (store, &iter,
//                          COLUMN_TRACKNUMBER, data[i].tracknumber,
//                          COLUMN_ARTIST, data[i].artist,
//			  COLUMN_TITLE, data[i].title,
//			  COLUMN_ALBUM, data[i].album,
//			  COLUMN_LENGTH, data[i].length,
//                          -1);
//    }

  return GTK_TREE_MODEL (store);
}

int connect_server() {
  struct sockaddr_un addr;
  char buf[100];

  if ( (socket_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    // TODO Present message box to the user.
    // Possibly prompt to run the deamon
    perror("socket error");
    return -1;
  }

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);

  if (connect(socket_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    // TODO Present message box to the user.
    // Possibly prompt to run the deamon
    perror("connect error");
    return -1;
  }
}

void fetch_playlist() {
//  int rc = -1;
//  while( (rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
//    if (write(fd, buf, rc) != rc) {
//      if (rc > 0) fprintf(stderr,"partial write");
//      else {
//        perror("write error");
//        exit(-1);
//      }
//    }
//  }
}

void create_playlist(); 
void add_track(); 
void remove_track(); 
void repos_track();//reposition track
void add_deck();
void remove_deck();

void init_menus(vbox) {
    GtkWidget *daemon_menu = gtk_menu_new ();    /* Don't need to show menus */
    GtkWidget *connect_item = gtk_menu_item_new_with_label ("Connect");
    GtkWidget *preferences_item = gtk_menu_item_new_with_label ("Preferences");
    gtk_menu_append (GTK_MENU (daemon_menu), connect_item);
    gtk_menu_append (GTK_MENU (daemon_menu), preferences_item);
    gtk_widget_show (connect_item);
    gtk_widget_show (preferences_item);

    GtkWidget *menu_bar = gtk_menu_bar_new ();
    gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE,FALSE,0);
    //gtk_container_add (GTK_CONTAINER (vbox), menu_bar);
    gtk_widget_show (menu_bar);

    GtkWidget *file_item = gtk_menu_item_new_with_label ("File");
    gtk_widget_show (file_item);
}

void init_notebook_schedule(GtkWidget *notebook) {
    GtkWidget *treeview;
    GtkWidget *label; //we will use this for notebook's labels for pages
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;

    /* create a tree view */
    //model = create_model();
    treeview = gtk_tree_view_new();
    renderer = gtk_cell_renderer_text_new();

    /* column for rule number */ 
    column = gtk_tree_view_column_new_with_attributes("#",
            renderer,
            "text",
            COLUMN_ORDINAL,
            NULL);
    gtk_tree_view_append_column(treeview, column);

    /* column for type of the underlieng object. Either track or playlist*/
    column = gtk_tree_view_column_new_with_attributes("Type",
            renderer,
            "text",
            COLUMN_TYPE,
            NULL);
    gtk_tree_view_append_column(treeview, column);

    /* column for name (includes artists for tracks)*/
    column = gtk_tree_view_column_new_with_attributes("Name",
            renderer,
            "text",
            COLUMN_NAME,
            NULL);
    gtk_tree_view_append_column(treeview, column);

    /* column for Length*/
    column = gtk_tree_view_column_new_with_attributes("Length",
            renderer,
            "text",
            COLUMN_LENGTH,
            NULL);
    gtk_tree_view_append_column(treeview, column);

    /* column for the time when the item will play, considering uninterrupted playback*/
    column = gtk_tree_view_column_new_with_attributes("Time Start",
            renderer,
            "text",
            COLUMN_STARTTIME,
            NULL);
    gtk_tree_view_append_column(treeview, column);


    label = gtk_label_new("Schedule");
    gtk_notebook_append_page(notebook, treeview, label);
}

void init_notebook_playlists(GtkWidget *notebook) {
    GtkWidget *treeview;
    GtkWidget *label; //we will use this for notebook's labels for pages
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;

    /* create a tree view */
    //model = create_model();
    treeview = gtk_tree_view_new();
    renderer = gtk_cell_renderer_text_new();

    /* column for rule number */ 
    column = gtk_tree_view_column_new_with_attributes("#",
            renderer,
            "text",
            COLUMN_ORDINAL,
            NULL);
    gtk_tree_view_append_column(treeview, column);


    /* column for name (includes artists for tracks)*/
    column = gtk_tree_view_column_new_with_attributes("Name",
            renderer,
            "text",
            COLUMN_NAME,
            NULL);
    gtk_tree_view_append_column(treeview, column);

    /* column for Length*/
    column = gtk_tree_view_column_new_with_attributes("Length",
            renderer,
            "text",
            COLUMN_LENGTH,
            NULL);
    gtk_tree_view_append_column(treeview, column);

    /* column for the time when the item will play, considering uninterrupted playback*/
    column = gtk_tree_view_column_new_with_attributes("Time Start",
            renderer,
            "text",
            COLUMN_STARTTIME,
            NULL);
    gtk_tree_view_append_column(treeview, column);


    label = gtk_label_new("Playlists");
    gtk_notebook_append_page(notebook, treeview, label);

}

void init_notebook(GtkWidget *notebook) {
    init_notebook_schedule(notebook);
    init_notebook_playlists(notebook);
}


int main (int argc, char **argv){
    GtkWidget *slider;
    GtkTreePath *path;
    GtkTreeIter iter;
    GtkWidget *vbox, *hbox;
    GtkWidget *button_play, *button_play_image;
    GtkWidget * notebook = gtk_notebook_new();

    /* GTK initialisation */
    gtk_set_locale();
    gtk_init(&argc, &argv);
    mainwin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(mainwin), "delete_event",
            G_CALLBACK(gtk_exit), NULL);
    slider = gtk_hscale_new_with_range(0, SLIDER_LENGTH, 10);
    vbox = gtk_vbox_new (FALSE, 0);
    hbox = gtk_hbox_new (FALSE, 0);

    //We want button with icon only, no label
    button_play = gtk_toggle_button_new();
    button_play_image = gtk_image_new_from_stock(GTK_STOCK_MEDIA_PLAY, GTK_ICON_SIZE_BUTTON); //8kb
    gtk_button_set_label(button_play, NULL);
    gtk_button_set_image(button_play, button_play_image);

    init_notebook(notebook);
    init_menus(vbox);

    /* Layout */

    //Play button and Seek bar are on one line
    gtk_box_pack_start(GTK_BOX(hbox), button_play, FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox), slider, TRUE,TRUE,0);

    //below them is the playlist
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE,TRUE,0);
    gtk_container_add(GTK_CONTAINER(mainwin), vbox);

    gtk_widget_show_all (mainwin);

    if (connect_server() > 0) {
        char msg[] = "The daemon doesn't seem to be running. Start it first";
        GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
        gtk_message_dialog_new (mainwin, flags, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, msg);
    }
    gtk_main();
    return 0;
} 
