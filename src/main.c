#include <stdio.h>
#include <stdlib.h>

#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#define INIT_WINDOW_HEIGHT 280
#define INIT_WINDOW_WIDTH 450

#include "args.h"

gint start_x, start_y;
gboolean button_pressed = FALSE;

static gboolean on_button_press(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    if (event->button == 1) {
        start_x = event->x;
        start_y = event->y;
        button_pressed = TRUE;
    }
    return TRUE;
}

static gboolean on_button_release(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    if (event->button == 1) {
        button_pressed = FALSE;
    }
    return TRUE;
}

static gboolean on_motion_notify(GtkWidget *widget, GdkEventMotion *event, gpointer data) {
		GtkScrolledWindow *scrolled_window = GTK_SCROLLED_WINDOW(data);
		GtkAdjustment *adj = gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(scrolled_window));
        gdouble value = gtk_adjustment_get_value(adj) + (event->x - start_x);
        gtk_adjustment_set_value(adj, value);
        start_x = event->x;
        start_y = event->y;
    return TRUE;
}

int main (int argc, char *argv[]) {

    /* Read command line options */
    options_t options;
    options_parser(argc, argv, &options);

#ifdef DEBUG
    fprintf(stdout, "Command line options:\n");
    fprintf(stdout, "help: %d\n", options.help);
    fprintf(stdout, "version: %d\n", options.version);
    fprintf(stdout, "filename: %s\n", options.file_name);
#endif

#ifdef _WIN32
    window = gtk_window_new(GTK_WINDOW_POPUP);
#else
    gtk_init(&argc, &argv);
#endif
	
	// window
    GtkWindow *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Emoji Charmap");
	gtk_widget_set_size_request(GTK_WIDGET(window), INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    // create a hbox to hold the panels
    GtkWidget *hbox = gtk_vbox_new(FALSE, 5);
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // create top panel
    GtkWidget *panel1 = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), panel1, TRUE, TRUE, 0);

    // Create a scrollable area for the first panel
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_size_request(scrolled_window, INIT_WINDOW_WIDTH, 68);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);
	gtk_box_pack_start(GTK_BOX(panel1), scrolled_window, TRUE, TRUE, 0);

    // Create a fixed container for the clickable elements
    GtkWidget *fixed = gtk_fixed_new();
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), fixed);

    // Create the clickable elements and add them to the fixed container
    for (int i = 0; i < 30; i++) {
        GtkWidget *button = gtk_button_new_with_label("A");
        gtk_widget_set_size_request(button, 32, 32);
        gtk_fixed_put(GTK_FIXED(fixed), button, i * 32, 0);
    }

	// Connect the signals to the scrolled_window
    g_signal_connect(G_OBJECT(scrolled_window), "button-press-event", G_CALLBACK(on_button_press), scrolled_window);
    g_signal_connect(G_OBJECT(scrolled_window), "button-release-event", G_CALLBACK(on_button_release), scrolled_window);
    g_signal_connect(G_OBJECT(scrolled_window), "motion-notify-event", G_CALLBACK(on_motion_notify), scrolled_window);

	// ----------

    // create the second panel
    GtkWidget *panel2 = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), panel2, TRUE, TRUE, 0);
    gtk_widget_set_size_request(panel2, INIT_WINDOW_WIDTH, 256);

    // create a scrollable area for the second panel
    GtkWidget *scrolled_window1 = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window1), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(panel2), scrolled_window1, TRUE, TRUE, 0);

    // create a table for the emoji symbols
    GtkWidget *table = gtk_table_new(8, 8, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 2);
    gtk_table_set_col_spacings(GTK_TABLE(table), 2);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window1), table);

    // add emoji symbols to the table
    //for (int i = 0; i < 8; i++) {
    //    for (int j = 0; j < 8; j++) {
    //        GtkWidget *emoji_label = gtk_label_new("🙂");
    //        gtk_widget_set_size_request(emoji_label, 16, 32);
    //        gtk_table_attach_defaults(GTK_TABLE(table), emoji_label, i, i + 1, j, j + 1);
    //    }
    //}
	
	gchar *emoji_symbols[] = { "😀", "😃", "😄", "😁", "😆", "🥹", "😅", "😂", "🤣", "🥲", "☺️", "😊", "😇", "🙂", 
							  "🙃", "😉", "😌", "😍", "🥰", "😘", "😗", "😙", "😚", "😋", "😛", "😝", "😜", "🤪", 
							  "🤨", "🧐", "🤓", "😎", "🥸", "🤩", "🥳", "😏", "😒", "😞", "😔", "😟", "😕", "🙁", 
							  "☹️", "😣", "😖", "😫", "😩", "🥺", "😢", "😭", "😤", "😠", "😡", "🤬", "🤯", "😳", 
							  "🥵", "🥶", "😶‍", "😱", "😨", "😰", "😥", "😓", "🤗", "🤔", "🫣", "🤭", "🫢", "🫡", 
							  "🤫", "🫠", "🤥", "😶", "🫥", "😐", "🫤", "😑", "😬", "🙄", "😯", "😦", "😧", "😮", 
							  "😲", "🥱", "😴", "🤤", "😪", "😮‍💨", "😵", "😵‍💫", "🤐", "🥴", "🤢", "🤮", "🤧", 
							  "😷", "🤒", "🤕", "🤑", "🤠", "😈", "👿", "👹", "👺", "🤡", "💩", "👻", "💀", "☠️", 
							  "👽", "👾", "🤖", "🎃", "😺", "😸", "😹", "😻", "😼", "😽", "🙀", "😿", "😾" };

	// add emoji symbols to the table
	gshort cnt = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < (sizeof(emoji_symbols) / 8)/8 ; j++) {
			GtkWidget *emoji_label = gtk_label_new(emoji_symbols[++cnt]);
			// set font size
			PangoFontDescription *font_desc = pango_font_description_new();
			pango_font_description_set_size(font_desc, 12 * PANGO_SCALE);
			gtk_widget_modify_font(emoji_label, font_desc);
			gtk_widget_set_size_request(emoji_label, 32, 48);
			gtk_table_attach_defaults(GTK_TABLE(table), emoji_label, i, i + 1, j, j + 1);
		}
	}
	
	// close button
	GtkWidget *close_button = gtk_button_new_with_label("Close");
    //gtk_container_add(GTK_CONTAINER(container), close_button);

	// event creator
	g_signal_connect(G_OBJECT(close_button), "clicked", G_CALLBACK(gtk_main_quit), window);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // get screen
    GdkScreen *screen = gdk_screen_get_default();
    GdkRectangle rect;
    gdk_screen_get_monitor_geometry(screen, 0, &rect);

    int x,y;
	gdk_display_get_pointer(gdk_display_get_default(),NULL,&x,&y,NULL);

	// math screen outside
	gint winpos_x, winpos_y;
	gtk_window_get_position(GTK_WINDOW(window), &winpos_x, &winpos_y);
	
	if (x + winpos_x > rect.width)
		x = rect.width - winpos_x;
	if (y + winpos_y > rect.width)
		y = rect.height - winpos_y;

	// show window
	gtk_window_move(GTK_WINDOW(window),x,y);
    gtk_widget_show_all(window);

	gtk_main();

    return EXIT_SUCCESS;
}

