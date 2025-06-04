#define GTK_DISABLE_DEPRECATED
#include <gtk/gtk.h>
#include "Verification.hpp"

#include <gtk/gtk.h>

void show_message(GtkWindow* parent, const char* title, const char* message, GtkMessageType type) {
    GtkWidget *dialog = gtk_message_dialog_new(parent, GTK_DIALOG_DESTROY_WITH_PARENT, type, GTK_BUTTONS_OK, "%s", message);
    gtk_window_set_title(GTK_WINDOW(dialog), title);
    g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_destroy), NULL);
    gtk_window_present(GTK_WINDOW(dialog));
}

static void on_send_code_clicked(GtkButton *button, gpointer user_data) {
    RegisterData *data = (RegisterData *)user_data;
    GtkWindow *parent = GTK_WINDOW(gtk_widget_get_root(GTK_WIDGET(button)));

    show_message(parent, "Código enviado", "El código de verificación ha sido enviado a su teléfono o correo.", GTK_MESSAGE_INFO);
}

static void on_verify_clicked(GtkButton *button, gpointer user_data) {
    RegisterData *data = (RegisterData *)user_data;
    GtkWindow *parent = GTK_WINDOW(gtk_widget_get_root(GTK_WIDGET(button)));

    const gchar *input_code = gtk_editable_get_text(GTK_EDITABLE(data->verification_entry));

    if (g_strcmp0(input_code, "123456") == 0) {
        show_message(parent, "Verificación exitosa", "Código correcto. Registro completado.", GTK_MESSAGE_INFO);
    } else {
        show_message(parent, "Error", "Código incorrecto, intente de nuevo.", GTK_MESSAGE_ERROR);
    }
}

GtkWidget* create_page4(RegisterData *data) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(box, 20);
    gtk_widget_set_margin_bottom(box, 20);
    gtk_widget_set_margin_start(box, 20);
    gtk_widget_set_margin_end(box, 20);

    gtk_box_append(GTK_BOX(box), gtk_label_new("Ingrese el código de verificación enviado a su teléfono o correo:"));

    data->verification_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(data->verification_entry), "Código de verificación");
    gtk_box_append(GTK_BOX(box), data->verification_entry);

    GtkWidget *send_code_button = gtk_button_new_with_label("Enviar Código");
    gtk_box_append(GTK_BOX(box), send_code_button);
    g_signal_connect(send_code_button, "clicked", G_CALLBACK(on_send_code_clicked), data);

    GtkWidget *verify_button = gtk_button_new_with_label("Verificar Código");
    gtk_box_append(GTK_BOX(box), verify_button);
    g_signal_connect(verify_button, "clicked", G_CALLBACK(on_verify_clicked), data);

    return box;
}
