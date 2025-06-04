#include "ContactData.hpp"

GtkWidget* create_page2(RegisterData *data) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(box, 20);
    gtk_widget_set_margin_bottom(box, 20);
    gtk_widget_set_margin_start(box, 20);
    gtk_widget_set_margin_end(box, 20);

    // Teléfono principal
    data->phone_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(data->phone_entry), "Teléfono");
    gtk_box_append(GTK_BOX(box), gtk_label_new("Teléfono:"));
    gtk_box_append(GTK_BOX(box), data->phone_entry);

    // Teléfono alternativo
    data->alt_phone_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(data->alt_phone_entry), "Teléfono Alternativo");
    gtk_box_append(GTK_BOX(box), gtk_label_new("Teléfono Alternativo:"));
    gtk_box_append(GTK_BOX(box), data->alt_phone_entry);

    // Correo electrónico
    data->email_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(data->email_entry), "Correo Electrónico");
    gtk_box_append(GTK_BOX(box), gtk_label_new("Correo Electrónico:"));
    gtk_box_append(GTK_BOX(box), data->email_entry);

    return box;
}
