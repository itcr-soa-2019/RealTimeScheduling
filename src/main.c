/* 
   ____    ____     ___           ___    ____    ___   ____
  / ___/  / __ \   /   |         |__ \  / __ \  <  /  / __ \
  \__ \  / / / /  / /| |         __/ / / / / /  / /  / /_/ /
 ___/ / / /_/ /  / ___ |        / __/ / /_/ /  / /   \__, /
/____/  \____/  /_/  |_|       /____/ \____/  /_/   /____/

Instituto Tecnológico de Costa Rica
Maestría en Computación
Sistemas Operativos Avanzados
Prof: Francisco Torres Rojas, PHD.
Integrantes: Fabiola Espinoza
			 Nathalia Gonzalez
			 Manuel Figueroa
			 José Somarribas
			 Esteban Leandro
Proyecto 3: Real time Scheduling */

#include <gtk/gtk.h>
#include "stdio.h"

GtkBuilder *builder;

// Hide a thread info section
void show_task(GtkBuilder *builder, int index, int visible){
  GObject *id;
  GObject *te;
  GObject *pe;
  char* name = (char*) malloc(sizeof(char)*6);
  sprintf(name, "id_%d", index);
  char* executionTime = (char*) malloc(sizeof(char)*6);
  sprintf(executionTime, "te_%d", index);
  char* period = (char*) malloc(sizeof(char)*6);
  sprintf(period, "pe_%d", index);
  id = gtk_builder_get_object(builder, name);
  gtk_widget_set_visible(GTK_WIDGET(id), visible); //Make it visible
  te = gtk_builder_get_object(builder, executionTime);
  gtk_widget_set_visible(GTK_WIDGET(te), visible); //Make it visible
  pe = gtk_builder_get_object(builder, period);
  gtk_widget_set_visible(GTK_WIDGET(pe), visible); //Make it visible
}


/**
 * Show required tasks table lines
 */
void add_tasks() {
    GObject *spinBtn;
    spinBtn = gtk_builder_get_object (builder, "num_tasks");
    int tasks = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinBtn));
    if(tasks > 10) {
        tasks = 10;
    }
    for(size_t i = 0; i < 10; i++)
    {
        show_task(builder, i+1, 0);
        
    }  
    for(size_t i = 0; i < tasks; i++)
    {
        show_task(builder, i+1, 1);
    }
}



int initGtkUI(int argc, char **argv)
{ 
    GtkWidget *window;
    GObject *button;
    GObject *spinButton;
    GError *error = NULL;

    gtk_init (&argc, &argv);

    /* Construct a GtkBuilder instance and load our UI description */
    builder = gtk_builder_new ();
    if (gtk_builder_add_from_file (builder, "guiGTK.glade", &error) == 0)
    {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error (&error);
        return 1;
    }
    printf("Done");
    /* Connect signal handlers to the constructed widgets. */
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    button = gtk_builder_get_object (builder, "exit_btn");
    g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);
    button = gtk_builder_get_object (builder, "add_tasks");
    g_signal_connect (button, "clicked", G_CALLBACK (add_tasks), NULL);
    gtk_widget_show(window);
    gtk_main();
}

/**
 * Main execution method
 */
int main(int argc, char **argv)
{   
    //schedulerTesterWorkingExample(); //para que sirva, hay que comentar la creación de threads en initTaskList()
    initGtkUI(argc, argv);
}
