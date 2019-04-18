#include "createTex.h"



/**
 * Includes the description slide for the 
 * RM algorithm
 */
void includeRMDesc(FILE *output){
    FILE *rm = fopen("beamerFiles/rm.txt", "r");
    combineFiles(rm,output);
    fclose(rm);
}

/**
 * Includes the description slide for the EDF 
 * algorithm
 */
void includeEDFDesc(FILE *output){
    FILE *edf = fopen("beamerFiles/edf.txt", "r");
    combineFiles(edf,output);
    fclose(edf);
}

/**
 * Includes the  description slide for the LLF
 * algorithm
 */
void includeLLFDesc(FILE *output){
    FILE *llf = fopen("beamerFiles/llf.txt", "r");
    combineFiles(llf,output);
    fclose(llf);
}

/**
 * Includes the  schedulability Test Results
 */
void includeSchedTest(FILE *output){
    FILE *schedSlide = fopen("beamerFiles/SchedTest", "r");
    combineFiles(schedSlide, output);
    fclose(schedSlide);
}

/**
 * Creates a tex file to generate
 * the final presentation
 */
void createTexFile(execution_data *execution) {
    FILE *intro = fopen("beamerFiles/intro.txt", "r");
    FILE *close = fopen("beamerFiles/close.txt", "r");
    FILE *beamer = fopen("output/Presentacion.tex", "w");
    combineFiles(intro, beamer);
    // Algorithms Slides
    if(execution->RM > 0) {
        includeRMDesc(beamer);
    }
    if(execution->EDF > 0) {
         includeEDFDesc(beamer);
    }
    if(execution->LLF > 0) {
        includeLLFDesc(beamer);
    }
    /*Include Tests file */
    createTestResults(execution);
    includeSchedTest(beamer);
    combineFiles(close, beamer);
    fclose(close);
    fclose(intro);
    fclose(beamer); 
}




