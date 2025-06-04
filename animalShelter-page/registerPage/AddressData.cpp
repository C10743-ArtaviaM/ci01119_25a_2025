#include "AddressData.hpp"
#include "locations.hpp"
#include <map>
#include <vector>
#include <string>

// Estructura de datos para ubicaciones
extern std::map<std::string, std::map<std::string, std::vector<std::string>>> locations;

static void on_province_changed(GtkComboBoxText *combo, gpointer user_data) {
    RegisterData *data = (RegisterData *)user_data;
    const gchar *province = gtk_combo_box_text_get_active_text(combo);

    // Limpiar y actualizar cantones
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(data->canton_combo));
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(data->district_combo));

    if (province && locations.count(province)) {
        for (const auto &canton : locations[province]) {
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(data->canton_combo), canton.first.c_str());
        }
        gtk_combo_box_set_active(GTK_COMBO_BOX(data->canton_combo), 0);
    }
}

static void on_canton_changed(GtkComboBoxText *combo, gpointer user_data) {
    RegisterData *data = (RegisterData *)user_data;
    const gchar *province = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data->province_combo));
    const gchar *canton = gtk_combo_box_text_get_active_text(combo);

    // Limpiar y actualizar distritos
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(data->district_combo));

    if (province && canton && locations.count(province) && locations[province].count(canton)) {
        for (const auto &distrito : locations[province][canton]) {
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(data->district_combo), distrito.c_str());
        }
        gtk_combo_box_set_active(GTK_COMBO_BOX(data->district_combo), 0);
    }
}

GtkWidget* create_page3(RegisterData *data) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(box, 20);
    gtk_widget_set_margin_bottom(box, 20);
    gtk_widget_set_margin_start(box, 20);
    gtk_widget_set_margin_end(box, 20);

    // Provincia
    gtk_box_append(GTK_BOX(box), gtk_label_new("Provincia:"));
    data->province_combo = gtk_combo_box_text_new();
    for (const auto &provincia : locations) {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(data->province_combo), provincia.first.c_str());
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(data->province_combo), 0);
    gtk_box_append(GTK_BOX(box), data->province_combo);

    // Cantón
    gtk_box_append(GTK_BOX(box), gtk_label_new("Cantón:"));
    data->canton_combo = gtk_combo_box_text_new();
    gtk_box_append(GTK_BOX(box), data->canton_combo);

    // Distrito
    gtk_box_append(GTK_BOX(box), gtk_label_new("Distrito:"));
    data->district_combo = gtk_combo_box_text_new();
    gtk_box_append(GTK_BOX(box), data->district_combo);

    // Dirección Exacta
    gtk_box_append(GTK_BOX(box), gtk_label_new("Dirección Exacta:"));
    data->exact_address = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(data->exact_address), GTK_WRAP_WORD_CHAR);
    gtk_widget_set_size_request(data->exact_address, -1, 80);
    gtk_box_append(GTK_BOX(box), data->exact_address);

    // Conectar señales
    g_signal_connect(data->province_combo, "changed", G_CALLBACK(on_province_changed), data);
    g_signal_connect(data->canton_combo, "changed", G_CALLBACK(on_canton_changed), data);

    // Inicializar cantones y distritos
    on_province_changed(GTK_COMBO_BOX_TEXT(data->province_combo), data);

    return box;
}
