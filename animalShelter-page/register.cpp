#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <iostream>
#include <string>

struct RegisterData {
    GtkWidget *username_entry;
    GtkWidget *password_entry;
    GtkWidget *confirm_entry;
};

static void show_message(GtkWindow *parent, const char *title, const char *message, GtkMessageType type) {
    GtkWidget *dialog = gtk_message_dialog_new(
        parent,
        GTK_DIALOG_DESTROY_WITH_PARENT,
        type,
        GTK_BUTTONS_OK,
        "%s",
        message
    );
    gtk_window_set_title(GTK_WINDOW(dialog), title);
    g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_destroy), NULL);
    gtk_window_present(GTK_WINDOW(dialog));
}

static void on_register_clicked(GtkButton *button, gpointer user_data) {
    RegisterData *reg_data = (RegisterData *)user_data;

    const gchar *username = gtk_editable_get_text(GTK_EDITABLE(reg_data->username_entry));
    const gchar *password = gtk_editable_get_text(GTK_EDITABLE(reg_data->password_entry));
    const gchar *confirm   = gtk_editable_get_text(GTK_EDITABLE(reg_data->confirm_entry));

    GtkWindow *parent = GTK_WINDOW(gtk_widget_get_root(GTK_WIDGET(button)));

    if (std::string(password) != confirm) {
        show_message(parent, "Error", "Passwords do not match", GTK_MESSAGE_ERROR);
        return;
    }

    std::string registration = "REGISTER:" + std::string(username) + ":" + std::string(password) + "\n";

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        show_message(parent, "Error", "Could not create socket", GTK_MESSAGE_ERROR);
        return;
    }

    struct sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        show_message(parent, "Error", "Could not connect to server", GTK_MESSAGE_ERROR);
        close(sock);
        return;
    }

    send(sock, registration.c_str(), registration.size(), 0);

    char buffer[128] = {0};
    ssize_t bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    close(sock);

    if (bytes_received <= 0) {
        show_message(parent, "Error", "No response from server", GTK_MESSAGE_ERROR);
    } else {
        buffer[bytes_received] = '\0';
        std::string response = buffer;
        if (response == "OK\n") {
            show_message(parent, "Success", "Registration successful!", GTK_MESSAGE_INFO);
        } else {
            show_message(parent, "Error", "Registration failed", GTK_MESSAGE_ERROR);
        }
    }
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Register");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 250);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(box, 20);
    gtk_widget_set_margin_bottom(box, 20);
    gtk_widget_set_margin_start(box, 20);
    gtk_widget_set_margin_end(box, 20);
    gtk_window_set_child(GTK_WINDOW(window), box);

    GtkWidget *username_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Username");
    gtk_box_append(GTK_BOX(box), username_entry);

    GtkWidget *password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_box_append(GTK_BOX(box), password_entry);

    GtkWidget *confirm_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(confirm_entry), "Confirm Password");
    gtk_entry_set_visibility(GTK_ENTRY(confirm_entry), FALSE);
    gtk_box_append(GTK_BOX(box), confirm_entry);

    GtkWidget *register_button = gtk_button_new_with_label("Register");
    gtk_box_append(GTK_BOX(box), register_button);

    RegisterData *reg_data = new RegisterData;
    reg_data->username_entry = username_entry;
    reg_data->password_entry = password_entry;
    reg_data->confirm_entry = confirm_entry;

    g_signal_connect(register_button, "clicked", G_CALLBACK(on_register_clicked), reg_data);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new("com.example.register", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
