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
#include "scheduling/scheduling.h"

GtkBuilder *builder;
GtkWidget *window;

int tasks;

static void
on_response (GtkDialog *dialog,
             gint       response_id,
             gpointer   user_data)
{
  /* Destroy the dialog after one of the above actions have taken place */
  gtk_widget_destroy (GTK_WIDGET (dialog));

}

/**
 * Show a dialog when the execution time is greater than
 * the period time
 */
void showErrorDialog(int task) {
    GtkWidget *dialog;
    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    char* error = (char*) malloc(sizeof(char)*80);
    sprintf(error,"El periodo de la Tarea %d tiene que ser mayor o igual que el tiempo de ejecución", task);
    dialog = gtk_message_dialog_new (GTK_WINDOW(window), GTK_DIALOG_MODAL, 
                                            GTK_MESSAGE_WARNING, 
                                            GTK_BUTTONS_OK, 
                                            "%s",error);
    gtk_widget_show(dialog);
    g_signal_connect (GTK_DIALOG (dialog), "response", 
                    G_CALLBACK (on_response), NULL);
}

/**
 * Set visibility for a task row
 */
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
 * Validates the input data before start processing
 */
int validateData(GtkBuilder *builder, int index, task_t *task) {
  GObject *te;
  GObject *pe;
  char* executionTime = (char*) malloc(sizeof(char)*6);
  sprintf(executionTime, "te_%d", index);
  char* period = (char*) malloc(sizeof(char)*6);
  sprintf(period, "pe_%d", index);
  te = gtk_builder_get_object(builder, executionTime);
  pe = gtk_builder_get_object(builder, period);
  int time = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(te));
  int ptime = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(pe));
  if(time > ptime) {
      showErrorDialog(index);
      return 1;
  }
  task->executionTime = time;
  task->periodTime = ptime;
  return 0;
}

/**
 * Show required tasks table lines
 */
void add_tasks() {
    GObject *spinBtn;
    spinBtn = gtk_builder_get_object (builder, "num_tasks");
    tasks = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinBtn));
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

/**
 * start
 */
void start_proc(){
    int error = 0;
    GObject *RM_Chk;
    GObject *EDF_Chk;
    GObject *LLF_Chk;
    GObject *Slides_Chk;
    RM_Chk = gtk_builder_get_object (builder, "RM_CHK");
    EDF_Chk = gtk_builder_get_object (builder, "EDF_CHK");
    LLF_Chk = gtk_builder_get_object (builder, "LLF_CHK");
    Slides_Chk = gtk_builder_get_object (builder, "IND_CHK");
    CurrentExecution.Slides = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Slides_Chk));
    task_t taskData[tasks];
    for(size_t i = 0; i < tasks; i++)
    {
        error += validateData(builder, i+1, &taskData[i]);
    }
    if(error > 0){
        return; // Some tasks data are incorrect.
    }
    CurrentExecution.RM = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(RM_Chk));
    CurrentExecution.EDF = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(EDF_Chk));
    CurrentExecution.LLF = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(LLF_Chk));
    CurrentExecution.tasks = taskData;
    if((CurrentExecution.RM + CurrentExecution.EDF + CurrentExecution.LLF) > 0){
        CurrentExecution.count = tasks;
        execute_Scheduling(CurrentExecution);
        return;
    }
    else{
    GtkWidget *dialog;
    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    char* error = (char*) malloc(sizeof(char)*80);
    sprintf(error,"Debe escoger al menos un algoritmo para la simulación");
    dialog = gtk_message_dialog_new (GTK_WINDOW(window), GTK_DIALOG_MODAL, 
                                            GTK_MESSAGE_WARNING, 
                                            GTK_BUTTONS_OK, 
                                            "%s", error);
    gtk_widget_show(dialog);
    g_signal_connect (GTK_DIALOG (dialog), "response", 
                    G_CALLBACK (on_response), NULL);
    }
}

int initGtkUI(int argc, char **argv)
{ 
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
    /* Connect signal handlers to the constructed widgets. */
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    button = gtk_builder_get_object (builder, "exit_btn");
    g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);
    button = gtk_builder_get_object (builder, "add_tasks");
    g_signal_connect (button, "clicked", G_CALLBACK (add_tasks), NULL);
    button = gtk_builder_get_object (builder, "proc_btn");
    g_signal_connect (button, "clicked", G_CALLBACK (start_proc), NULL);
    gtk_widget_show(window);
    gtk_main();
}

/**
 * Main execution method
 */
int main(int argc, char **argv)
{   
    initGtkUI(argc, argv);
}
