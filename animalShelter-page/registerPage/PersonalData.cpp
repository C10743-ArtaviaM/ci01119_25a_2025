#include "PersonalData.hpp"

GtkWidget* create_page1(RegisterData *data) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(box, 20);
    gtk_widget_set_margin_bottom(box, 20);
    gtk_widget_set_margin_start(box, 20);
    gtk_widget_set_margin_end(box, 20);

    // Tipo de documento
    data->document_type_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(data->document_type_combo), "Cédula");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(data->document_type_combo), "Pasaporte");
    gtk_box_append(GTK_BOX(box), gtk_label_new("Tipo de documento:"));
    gtk_box_append(GTK_BOX(box), data->document_type_combo);

    // Nombre
    data->first_name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(data->first_name_entry), "Nombre");
    gtk_box_append(GTK_BOX(box), data->first_name_entry);

    // Apellido
    data->last_name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(data->last_name_entry), "Apellido");
    gtk_box_append(GTK_BOX(box), data->last_name_entry);

    // Fecha de nacimiento
    data->birth_calendar = gtk_calendar_new();
    gtk_box_append(GTK_BOX(box), gtk_label_new("Fecha de nacimiento:"));
    gtk_box_append(GTK_BOX(box), data->birth_calendar);

    // Contraseña
    data->password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(data->password_entry), "Contraseña");
    gtk_entry_set_visibility(GTK_ENTRY(data->password_entry), FALSE);
    gtk_box_append(GTK_BOX(box), data->password_entry);

    // Confirmación
    data->confirm_password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(data->confirm_password_entry), "Confirmar Contraseña");
    gtk_entry_set_visibility(GTK_ENTRY(data->confirm_password_entry), FALSE);
    gtk_box_append(GTK_BOX(box), data->confirm_password_entry);

    return box;
}
