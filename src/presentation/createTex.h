#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * Creates a tex file to generate
 * the final presentation
 */
void createTexFile() {
    FILE *intro = fopen("beamerFiles/intro.txt", "r");
    FILE *beamer = fopen("output/Presentacion.tex", "w");
    combineFiles(intro,beamer);
    fclose(intro);
    fclose(beamer); 
}

