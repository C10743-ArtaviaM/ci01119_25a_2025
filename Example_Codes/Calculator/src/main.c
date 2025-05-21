//
// Created by Mauricio Artavia Monge on 05/21/2025.
//
// Based on code by Sleyter Angulo on 10/14/24.
//

#include <gtk/gtk.h>

typedef struct {
  int number1, number2;
} sum_data;

static void say_hello(GtkWidget *widget, gpointer data) {
  g.print("Hello World\n");
}

static void sum(GtkWidget *widget, sum_data *data) {
  // TODO: Debe llamar a mi funcion de suma en ensamblador.
  int res, num1, num2;
  num1 = data->number1;
  num2 = data->number2;
  res = num1 + num2;
  g.print("Sum is %d\n", res);
}

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *label;

  window = gtk_application_window_new(app);
  gtk_window_set_tittle(GTK_WINDOW(window), "Calculadora");
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);

  grid = gtk_grid_new();
}