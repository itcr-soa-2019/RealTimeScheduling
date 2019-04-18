#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedulability.h"

/**
 * Puts the content of a file inside the output file
 */
void combineFiles(FILE *input, FILE *output) {
    char c;
    while ((c = fgetc(input)) != EOF){
        fputc(c, output);
    }
}

/**
 * Create a latex table to represent the 
 * execution of an algorithm
 */
void createResultTable(int *resultTable, int units, int tasks, char *alg){
    FILE* table = fopen("beamerFiles/tempTable", "w");
    const char *cell_content[10];
    cell_content[0] = "& \\cellcolor{orange} T1";
    cell_content[1] = "& \\cellcolor{olive} T2";
    cell_content[2] = "& \\cellcolor{lime} T3";
    cell_content[3] = "& \\cellcolor{purple} T4";
    cell_content[4] = "& \\cellcolor{yellow} T5";
    cell_content[5] = "& \\cellcolor{pink} T6";
    cell_content[6] = "& \\cellcolor{teal} T7";
    cell_content[7] = "& \\cellcolor{violet} T8";
    cell_content[8] = "& \\cellcolor{cyan} T9";
    cell_content[9] = "& \\cellcolor{magenta} T10"; 
    
    fprintf(table,"%s %s", "\\begin{table}","\n");
    fprintf(table,"%s %s", "\\begin{center}","\n");
    char str[512];
    strcpy(str,"\\begin{tabular}{|l|");
    for(int i=0;i < units;i++){
        strcat(str,"l|");
    }
    strcat(str,"}");
    fprintf(table,"%s %s", str, "\n");
    fprintf(table,"%s %s", "\\hline", "\n");

    fprintf(table,"%s", "\\textbf{Detalle}");
    for(int i=0;i < units;i++){
        fprintf(table,"%s%d%s", "& \\textbf{",i+1,"}");
    }
    fprintf(table,"%s %s", "\\\\ \\hline", "\n");
    fprintf(table,"%s ", "Estado");
    for(int i=0;i < units;i++){
        fprintf(table,"%s", "& \\cellcolor{green} ");
    }
    fprintf(table,"%s %s", "\\\\ \\hline", "\n");
    for(int i = 0; i < tasks; i++)
    {
        fprintf(table,"%s%d", "T",i+1);
        for(int j = 0; j < units; j++)
        {
            printf("I:%d  J:%d",i,j);
            if(*(resultTable+i*units + j) == 0){
                fprintf(table,"%s", "& ");
            }
             else {
                 fprintf(table,"%s", cell_content[i]);
            }
        }
        fprintf(table,"%s %s", "\\\\ \\hline", "\n");
        
    }
    
    fprintf(table,"%s %s", "\\end{tabular}","\n");
    fprintf(table,"%s %s %s", "\\caption{Ejecución", alg, "}\n");
    fprintf(table,"%s %s", "\\end{center}","\n");
    fprintf(table,"%s %s", "\\end{table}","\n");
    fclose(table);
}


void createLLFResultSlide(FILE *output, execution_data *execution) {
    FILE *schedSlide = fopen("beamerFiles/LLFResultSlide", "w");
 
    fprintf(schedSlide,"%s %s","\\begin{frame}","\n");
    fprintf(schedSlide,"%s %s", "\\frametitle{Resultado de Ejecución para LLF}","\n");
    createResultTable(execution->LLF_Table, execution->timeUnits, execution->count, "Least Laxity");            
    FILE* table = fopen("beamerFiles/tempTable", "r");
    combineFiles(table,schedSlide);
    fclose(table);
    fprintf(schedSlide,"%s %s", "\\end{frame}","\n");
    fclose(schedSlide);
    FILE *read = fopen("beamerFiles/LLFResultSlide", "r");
    combineFiles(read,output);
    fclose(read);
}

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
    createLLFResultSlide(schedSlide, execution);
    fclose(schedSlide);

}



