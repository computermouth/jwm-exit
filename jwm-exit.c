#include <stdio.h>
#include <gtk/gtk.h>


void logout_btn_clicked(GtkWidget *widget, gpointer data){
    system("jwm -exit");
}

void suspend_btn_clicked(GtkWidget *widget, gpointer data){
    system("xscreensaver-command -lock");
    system("systemctl suspend");
}

void reboot_btn_clicked(GtkWidget *widget, gpointer data){
    system("systemctl reboot");
}

void poweroff_btn_clicked(GtkWidget *widget, gpointer data){
    system("systemctl poweroff");
}

GdkPixbuf *create_pixbuf(const gchar *filename){
	GdkPixbuf *pixbuf;
	GError *error = NULL;
	pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	
	if (!pixbuf) {
		fprintf(stderr, "%s\n", error->message);
		g_error_free(error);
	}
	
	return pixbuf;
}


int main(int argc, char *argv[]) {
	
	GtkWidget *window;
	GtkWidget *cancel_btn;
	GtkWidget *logout_btn;
	GtkWidget *suspend_btn;
	GtkWidget *reboot_btn;
	GtkWidget *poweroff_btn;
	GtkWidget *hbox_bot;
	
	GtkIconTheme *theme;
	theme = gtk_icon_theme_get_default();
	
	GdkPixbuf *window_icon;

	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Chip Power");
	gtk_window_set_default_size(GTK_WINDOW(window), 470, 272);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);
    
    window_icon = create_pixbuf("gtk-stop");
    gtk_window_set_icon(GTK_WINDOW(window), window_icon);

	GtkWidget *align;
	align = gtk_alignment_new(0, 1, 1, 0.4);

    hbox_bot = gtk_hbox_new(TRUE, 1);
    gtk_container_add(GTK_CONTAINER(align), hbox_bot);
    gtk_container_add(GTK_CONTAINER(window), align);
	
	cancel_btn = gtk_button_new_from_stock("gtk-cancel");
	gtk_widget_set_tooltip_text(cancel_btn, "Button widget");
	
	logout_btn = gtk_button_new_with_label("Logout");
	gtk_widget_set_tooltip_text(logout_btn, "Button widget");
	
	suspend_btn = gtk_button_new_with_label("Suspend");
	gtk_widget_set_tooltip_text(suspend_btn, "Button widget");
	
	reboot_btn = gtk_button_new_with_label("Reboot");
	gtk_widget_set_tooltip_text(reboot_btn, "Button widget");
	
	poweroff_btn = gtk_button_new_with_label("Power Off");
	gtk_widget_set_tooltip_text(poweroff_btn, "Button widget");
	
	gtk_box_pack_start(GTK_BOX(hbox_bot), cancel_btn, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_bot), logout_btn, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_bot), suspend_btn, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_bot), reboot_btn, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_bot), poweroff_btn, TRUE, TRUE, 0);
	
	
	g_signal_connect(G_OBJECT(window), "destroy",
		G_CALLBACK(gtk_main_quit), NULL);
		
	g_signal_connect(G_OBJECT(cancel_btn), "clicked",
		G_CALLBACK(gtk_main_quit), NULL);
		
	g_signal_connect(G_OBJECT(logout_btn), "clicked",
		G_CALLBACK(logout_btn_clicked), NULL);
		
	g_signal_connect(G_OBJECT(suspend_btn), "clicked",
		G_CALLBACK(suspend_btn_clicked), NULL);
		
	g_signal_connect(G_OBJECT(reboot_btn), "clicked",
		G_CALLBACK(reboot_btn_clicked), NULL);
		
	g_signal_connect(G_OBJECT(poweroff_btn), "clicked",
	    G_CALLBACK(poweroff_btn_clicked), NULL);

	gtk_widget_show_all(window);

    g_object_unref(window_icon);
	
	gtk_main();
	
	return 0;
	
}
