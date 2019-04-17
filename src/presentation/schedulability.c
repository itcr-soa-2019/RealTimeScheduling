#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedulability.h"

void createTestResults(execution_data *execution) {
   FILE *schedSlide = fopen("beamerFiles/SchedTest", "w");
   if(execution->RM > 0) {
        fprintf(schedSlide,"%s %s","\\begin{frame}","\n");
        fprintf(schedSlide,"%s %s", "\\frametitle{Tests de Schedulability RM}","\n");
        fprintf(schedSlide,"%s %s", "\\begin{table}","\n");
        fprintf(schedSlide,"%s %s", "\\begin{center}","\n");
        fprintf(schedSlide,"%s %s", "\\caption{Datos de Ejecución}","\n");
        fprintf(schedSlide,"%s %s", "\\label{Tabla 1}","\n");
        fprintf(schedSlide,"%s %s", "\\begin{tabular}{|l|l|l}", "\n");
        fprintf(schedSlide,"%s %s", "\\hline", "\n");
        fprintf(schedSlide,"%s %s", "\\textbf{Tarea} & \\textbf{Tiempo Ejecucion $C_{i}$} & \\textbf{Periodo $T_{i}$} \\\\", "\n");
        for(int i = 0; i < execution->count; i++)
        {
        fprintf(schedSlide,"%d %s %d %s %d", i+1, "&", 
                execution->tasks[i].executionTime, "&", execution->tasks[i].periodTime);    
        fprintf(schedSlide,"%s %s", "\\\\ \\hline", "\n");      
        }
        fprintf(schedSlide,"%s %s", "\\end{tabular}","\n");
        fprintf(schedSlide,"%s %s", "\\end{center}","\n");
        fprintf(schedSlide,"%s %s", "\\end{table}","\n");

        fprintf(schedSlide,"%s %s", "Este conjunto de tareas es schedulable por RM si: \\\\","\n");
        fprintf(schedSlide,"%s %s", "\\begin{center}","\n");
        fprintf(schedSlide,"%s %s", "$U_{p} = \\sum_{i=1}^{n} U_{i} \\leq  U_{n} = n(2^{\\frac{1}{n}}-1) < 0.7$","\n");
        fprintf(schedSlide,"%s %s", "\\end{center}","\n");
        fprintf(schedSlide,"%s %f %s %f %s ", "Para el conjunto dado $U_{p}$ es: ",execution->Up," y $U_{n}$ es: ", execution->Un, "\\\\ \n");
        if(execution->Un < 0.7) {
            fprintf(schedSlide,"%s %s", "Por lo tanto es un conjunto schedulable","\\\\ \n");
        }
        else {
            fprintf(schedSlide,"%s %s", "Por lo tanto es un conjunto \\textbf{no}  schedulable \\\\","\n");
        }
        
        fprintf(schedSlide,"%s %s", "\\end{frame}","\n");
    }
    if(execution->EDF > 0) {
        fprintf(schedSlide,"%s %s","\\begin{frame}","\n");
        fprintf(schedSlide,"%s %s", "\\frametitle{Tests de Schedulability EDF }","\n");
        fprintf(schedSlide,"%s %s", "\\begin{table}","\n");
        fprintf(schedSlide,"%s %s", "\\begin{center}","\n");
        fprintf(schedSlide,"%s %s", "\\caption{Datos de Ejecución}","\n");
        fprintf(schedSlide,"%s %s", "\\label{Tabla 1}","\n");
        fprintf(schedSlide,"%s %s", "\\begin{tabular}{|l|l|l}", "\n");
        fprintf(schedSlide,"%s %s", "\\hline", "\n");
        fprintf(schedSlide,"%s %s", "\\textbf{Tarea} & \\textbf{Tiempo Ejecucion $C_{i}$} & \\textbf{Periodo $T_{i}$} \\\\", "\n");
        for(int i = 0; i < execution->count; i++)
        {
        fprintf(schedSlide,"%d %s %d %s %d", i+1, "&", 
                execution->tasks[i].executionTime, "&", execution->tasks[i].periodTime);    
        fprintf(schedSlide,"%s %s", "\\\\ \\hline", "\n");      
        }
        fprintf(schedSlide,"%s %s", "\\end{tabular}","\n");
        fprintf(schedSlide,"%s %s", "\\end{center}","\n");
        fprintf(schedSlide,"%s %s", "\\end{table}","\n");

        fprintf(schedSlide,"%s %s", "Este conjunto de tareas es schedulable por RM si: \\\\","\n");
        fprintf(schedSlide,"%s %s", "\\begin{center}","\n");
        fprintf(schedSlide,"%s %s", "$U_{p} = \\sum_{i=1}^{n} \\frac{C_i}{T_i} <= 1$","\n");
        fprintf(schedSlide,"%s %s", "\\end{center}","\n");
        fprintf(schedSlide,"%s %f %s", "Para el conjunto dado $U_{p}$ es:",execution->Up, "\\\\ \n");
        if(execution->Up <= 1) {
            fprintf(schedSlide,"%s %s", "$U_{p} \\leq 1$ por lo tanto es un conjunto schedulable","\\\\ \n");
        }
        else {
            fprintf(schedSlide,"%s %s", "$U_{p} > 1$ por lo tanto es un conjunto \\textbf{no}  schedulable","\n");
        }
        
        fprintf(schedSlide,"%s %s", "\\end{frame}","\n");
    }
    if(execution->LLF > 0) {
        fprintf(schedSlide,"%s %s","\\begin{frame}","\n");
        fprintf(schedSlide,"%s %s", "\\frametitle{Tests de Schedulability LLF }","\n");
        fprintf(schedSlide,"%s %s", "\\begin{table}","\n");
        fprintf(schedSlide,"%s %s", "\\begin{center}","\n");
        fprintf(schedSlide,"%s %s", "\\caption{Datos de Ejecución}","\n");
        fprintf(schedSlide,"%s %s", "\\label{Tabla 1}","\n");
        fprintf(schedSlide,"%s %s", "\\begin{tabular}{|l|l|l}", "\n");
        fprintf(schedSlide,"%s %s", "\\hline", "\n");
        fprintf(schedSlide,"%s %s", "\\textbf{Tarea} & \\textbf{Tiempo Ejecucion $C_{i}$} & \\textbf{Periodo $T_{i}$} \\\\", "\n");
        for(int i = 0; i < execution->count; i++)
        {
        fprintf(schedSlide,"%d %s %d %s %d", i+1, "&", 
                execution->tasks[i].executionTime, "&", execution->tasks[i].periodTime);    
        fprintf(schedSlide,"%s %s", "\\\\ \\hline", "\n");      
        }
        fprintf(schedSlide,"%s %s", "\\end{tabular}","\n");
        fprintf(schedSlide,"%s %s", "\\end{center}","\n");
        fprintf(schedSlide,"%s %s", "\\end{table}","\n");

        fprintf(schedSlide,"%s %s", "Este conjunto de tareas es schedulable por RM si: \\\\","\n");
        fprintf(schedSlide,"%s %s", "\\begin{center}","\n");
        fprintf(schedSlide,"%s %s", "$U_{p} = \\sum_{i=1}^{n} \\frac{C_i}{T_i} <= 1$","\n");
        fprintf(schedSlide,"%s %s", "\\end{center}","\n");
        fprintf(schedSlide,"%s %f %s", "Para el conjunto dado $U_{p}$ es:",execution->Up, "\\\\ \n");
        if(execution->Up <= 1) {
            fprintf(schedSlide,"%s %s", "$U_{p} \\leq 1$ por lo tanto es un conjunto schedulable","\\\\ \n");
        }
        else {
            fprintf(schedSlide,"%s %s", "$U_{p} > 1$ por lo tanto es un conjunto \\textbf{no}  schedulable","\n");
        }
        
        fprintf(schedSlide,"%s %s", "\\end{frame}","\n");
    }
    fclose(schedSlide);


}