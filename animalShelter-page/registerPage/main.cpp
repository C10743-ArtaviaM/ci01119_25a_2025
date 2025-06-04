#define GTK_DISABLE_DEPRECATED
#include <gtk/gtk.h>
#include "RegisterData.hpp"
#include "PersonalData.hpp"
#include "ContactData.hpp"
#include "AddressData.hpp"
#include "Verification.hpp"

// Prototipos de validación (deberás implementar en cada página)
// ejemplo simple, solo para que compile
bool validate_page1(RegisterData* data) { return true; }
bool validate_page2(RegisterData* data) { return true; }
bool validate_page3(RegisterData* data) { return true; }
bool validate_page4(RegisterData* data) { return true; }


static void show_message(GtkWindow *parent, const char *title, const char *message, GtkMessageType type);

struct MainWindowData {
    GtkWidget *window;
    GtkWidget *stack;
    GtkWidget *continue_button;
    GtkWidget *back_button;
    RegisterData *reg_data;
    int current_page = 0;
};

static void update_buttons(MainWindowData *mw_data) {
    gtk_widget_set_sensitive(mw_data->back_button, mw_data->current_page > 0);

    bool valid = false;
    switch (mw_data->current_page) {
        case 0: valid = validate_page1(mw_data->reg_data); break;
        case 1: valid = validate_page2(mw_data->reg_data); break;
        case 2: valid = validate_page3(mw_data->reg_data); break;
        case 3: valid = validate_page4(mw_data->reg_data); break;
    }
    gtk_widget_set_sensitive(mw_data->continue_button, valid);
}

static void on_continue_clicked(GtkButton *button, gpointer user_data) {
    MainWindowData *mw_data = (MainWindowData *)user_data;

    if (mw_data->current_page == 3) {
        show_message(GTK_WINDOW(mw_data->window), "Completado", "Registro completado exitosamente", GTK_MESSAGE_INFO);
        return;
    }

    mw_data->current_page++;
    char *page_name = g_strdup_printf("page%d", mw_data->current_page + 1);
    gtk_stack_set_visible_child_name(GTK_STACK(mw_data->stack), page_name);
    g_free(page_name);

    update_buttons(mw_data);
}

static void on_back_clicked(GtkButton *button, gpointer user_data) {
    MainWindowData *mw_data = (MainWindowData *)user_data;

    if (mw_data->current_page == 0)
        return;

    mw_data->current_page--;
    char *page_name = g_strdup_printf("page%d", mw_data->current_page + 1);
    gtk_stack_set_visible_child_name(GTK_STACK(mw_data->stack), page_name);
    g_free(page_name);

    update_buttons(mw_data);
}

static void connect_validation_signals(MainWindowData *mw_data) {
    g_signal_connect(mw_data->reg_data->first_name_entry, "changed", G_CALLBACK(update_buttons), mw_data);
    g_signal_connect(mw_data->reg_data->last_name_entry, "changed", G_CALLBACK(update_buttons), mw_data);
    // Conecta aquí más señales según tus entradas
}

static void show_message(GtkWindow *parent, const char *title, const char *message, GtkMessageType type) {
    GtkWidget *dialog = gtk_message_dialog_new(parent, GTK_DIALOG_DESTROY_WITH_PARENT, type, GTK_BUTTONS_OK, "%s", message);
    gtk_window_set_title(GTK_WINDOW(dialog), title);
    g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_destroy), NULL);
    gtk_window_present(GTK_WINDOW(dialog));
}

int main(int argc, char *argv[]) {
    gtk_init();

    GMainLoop *loop = g_main_loop_new(NULL, FALSE);

    MainWindowData mw_data{};
    mw_data.reg_data = new RegisterData;

    mw_data.window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(mw_data.window), "Registro Multi-Página");
    gtk_window_set_default_size(GTK_WINDOW(mw_data.window), 400, 300);
    g_signal_connect(mw_data.window, "destroy", G_CALLBACK(g_main_loop_quit), loop);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(mw_data.window), vbox);

    mw_data.stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(mw_data.stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

    GtkWidget *page1 = create_page1(mw_data.reg_data);
    GtkWidget *page2 = create_page2(mw_data.reg_data);
    GtkWidget *page3 = create_page3(mw_data.reg_data);
    GtkWidget *page4 = create_page4(mw_data.reg_data);

    gtk_stack_add_named(GTK_STACK(mw_data.stack), page1, "page1");
    gtk_stack_add_named(GTK_STACK(mw_data.stack), page2, "page2");
    gtk_stack_add_named(GTK_STACK(mw_data.stack), page3, "page3");
    gtk_stack_add_named(GTK_STACK(mw_data.stack), page4, "page4");

    gtk_box_append(GTK_BOX(vbox), mw_data.stack);

    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(vbox), button_box);

    mw_data.back_button = gtk_button_new_with_label("Anterior");
    gtk_box_append(GTK_BOX(button_box), mw_data.back_button);
    g_signal_connect(mw_data.back_button, "clicked", G_CALLBACK(on_back_clicked), &mw_data);

    mw_data.continue_button = gtk_button_new_with_label("Continuar");
    gtk_box_append(GTK_BOX(button_box), mw_data.continue_button);
    g_signal_connect(mw_data.continue_button, "clicked", G_CALLBACK(on_continue_clicked), &mw_data);

    gtk_stack_set_visible_child_name(GTK_STACK(mw_data.stack), "page1");
    mw_data.current_page = 0;

    connect_validation_signals(&mw_data);
    update_buttons(&mw_data);

    gtk_widget_show(mw_data.window);
    g_main_loop_run(loop);
    g_main_loop_unref(loop);

    delete mw_data.reg_data;
    return 0;
}
