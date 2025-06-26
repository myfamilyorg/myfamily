#include <gtk/gtk.h>
#include <string.h>  // For strcat
#include <unistd.h>  // For getcwd
#include <webkit2/webkit2.h>

static void destroy_window_cb(GtkWidget *widget, gpointer data) {
	gtk_main_quit();
}

int main(int argc, char *argv[]) {
	// Initialize GTK
	gtk_init(&argc, &argv);

	// Create a new GTK window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "MyFamily");
	gtk_window_fullscreen(
	    GTK_WINDOW(window));  // Keep full-screen from previous request
	g_signal_connect(window, "destroy", G_CALLBACK(destroy_window_cb),
			 NULL);

	// Create a WebKit web view
	WebKitWebView *web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
	GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(scrolled_window), GTK_WIDGET(web_view));
	gtk_container_add(GTK_CONTAINER(window), scrolled_window);

	// Get the current working directory
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		g_print("Error getting current working directory\n");
		return 1;
	}

	const char *relative_path = "resources/kiosk.html";

	char file_uri[2048] = "file://";
	strcat(file_uri, cwd);
	strcat(file_uri, "/");
	strcat(file_uri, relative_path);

	// Load the local file
	webkit_web_view_load_uri(web_view, file_uri);

	// Show all widgets
	gtk_widget_show_all(window);

	// Start the GTK main loop
	gtk_main();

	return 0;
}
