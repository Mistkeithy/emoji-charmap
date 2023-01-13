#include <stdio.h>
#include <stdlib.h>

#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#define INIT_WINDOW_HEIGHT 280
#define INIT_WINDOW_WIDTH 450

#include "args.h"

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

    gtk_init(&argc, &argv);

	// window
    GtkWindow *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Emoji Charmap");
	gtk_widget_set_size_request(GTK_WIDGET(window), INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	// objects
    GtkWidget *close_button = gtk_button_new_with_label("Close");
    gtk_container_add(GTK_CONTAINER(window), close_button);

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

