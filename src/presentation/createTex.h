#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "schedulability.h"

/**
 * Puts the content of a file inside the output file
 */
void combineFiles(FILE *input, FILE *output);


/**
 * Includes the description slide for the 
 * RM algorithm
 */
void includeRMDesc(FILE *output);

/**
 * Includes the description slide for the EDF 
 * algorithm
 */
void includeEDFDesc(FILE *output);

/**
 * Includes the  description slide for the LLF
 * algorithm
 */
void includeLLFDesc(FILE *output);

/**
 * Creates a tex file to generate
 * the final presentation
 */
void createTexFile(execution_data *execution);




