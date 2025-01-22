#include "ldpc_utils.h"
#include "sampling_utils.h"
#include <stdbool.h>

//void gen_H(unsigned long H_cols[COLUMN_WEIGHT*CODE_LENGTH]){
int gen_H(unsigned long *H_cols, int *row_weights){

    unsigned long col_support[COLUMN_WEIGHT];
	
	for(int i = 0; i < CODE_REDUNDANCY; i++){
		row_weights[i] = 0;
	}
	
    for(int i = 0;i<CODE_LENGTH; i++){
		
        /*First sample COLUMN_WEIGHT different positions, then sort them */
        sample_col(col_support); //sample positions
        mergeSort(col_support, 0, COLUMN_WEIGHT-1); //sort positions

        /*Now, assign positions and update row weights*/
        for(int j = 0; j < COLUMN_WEIGHT; j++){
           H_cols[i*COLUMN_WEIGHT+j] = col_support[j];
		   row_weights[col_support[j]] ++;
        }
		
    }
	
	/*Compute maximum row weight*/
	int max_row_weight = 0;
	for(int i = 0; i<CODE_REDUNDANCY; i++){
		if(row_weights[i]>max_row_weight){
			max_row_weight = row_weights[i];
		}
	}
	
	return max_row_weight;
}

//void gen_H(unsigned long H_cols[COLUMN_WEIGHT*CODE_LENGTH]){
void compute_H_row_supports(const unsigned long *H_cols, const int max_row_weight, unsigned long *H_rows){

	int counters_num_elements[CODE_REDUNDANCY]; //counts number of values for each row
	for(int i = 0; i< CODE_REDUNDANCY; i++){
		counters_num_elements[i] = 0;
	}
	
	for(int i = 0; i<CODE_LENGTH;i++){
		for(int j = 0; j<COLUMN_WEIGHT; j++){
			unsigned long x = H_cols[i*COLUMN_WEIGHT + j];
			H_rows[x*max_row_weight+counters_num_elements[x]] = (unsigned long) i;
			counters_num_elements[x] ++;
		}
	}
}
	
	
void compute_syndrome(unsigned long *err_support, unsigned long *H_cols, unsigned int *syndrome, const int t){
	
	//assign all syndrome values to 0
	for(int i = 0;i < CODE_REDUNDANCY; i++){
		syndrome[i] = 0;
	}
	
	//start modifying syndrome
	for(int i = 0; i < t; i++){
		int pos = err_support[i];
		for(int j = 0; j<COLUMN_WEIGHT; j++){
			syndrome[H_cols[pos*COLUMN_WEIGHT+j]] = syndrome[H_cols[pos*COLUMN_WEIGHT+j]]^1;
		}
	}
}

void write_H(unsigned long H_cols[COLUMN_WEIGHT*CODE_LENGTH]){

   FILE *fptr;

   // Open a file in writing mode
   fptr = fopen("H.txt", "w");
   for(int i = 0;i<COLUMN_WEIGHT*CODE_LENGTH-1;i++){
      // Write some text to the file
      fprintf(fptr, "%d,",H_cols[i]);
   }
   fprintf(fptr, "%d",H_cols[COLUMN_WEIGHT*CODE_LENGTH-1]);
}