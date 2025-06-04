#pragma once
#include <gtk/gtk.h>

struct RegisterData {
    // Page 1
    GtkWidget *document_type_combo;
    GtkWidget *first_name_entry;
    GtkWidget *last_name_entry;
    GtkWidget *birth_calendar;
    GtkWidget *password_entry;
    GtkWidget *confirm_password_entry;

    // Page 2
    GtkWidget *phone_entry;
    GtkWidget *alt_phone_entry;
    GtkWidget *email_entry;

    // Page 3
    GtkWidget *province_combo;
    GtkWidget *canton_combo;
    GtkWidget *district_combo;
    GtkWidget *exact_address;

    // Page 4
    GtkWidget *verification_entry;
};
