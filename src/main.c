#include "params.h"
#include "QC_utils.h"
//#include "ldpc_utils.h"
#include <stdio.h>
#include "sampling_utils.h"
#include <stdlib.h>
#include <time.h>
#include "QC_bf.h"

int main() {

	srand (INITIAL_SEED);
	
	//Initialize file for writing output
	//Format: n_r_v_SEED
	char *file_output = (char*)malloc(50 * sizeof(char));
	sprintf(file_output, "QC_results_%d_%d_%d.txt", CODE_REDUNDANCY, COLUMN_WEIGHT, INITIAL_SEED);
	
	char *file_log = (char*)malloc(50 * sizeof(char));
	sprintf(file_log, "QC_log_%d_%d_%d.txt", CODE_REDUNDANCY, COLUMN_WEIGHT, INITIAL_SEED);
	
	//Open files in write mode to overwrite (in case files already existed)
	FILE *fptr_out;
	fptr_out = fopen(file_output, "w");
	fclose(fptr_out);

	FILE *fptr_log;
	fptr_log = fopen(file_log, "w");
	fclose(fptr_log);	
   
	//represent H as h1 (support of first column) and h2 (support of second column)
    unsigned long *h1, *h2, *H_first_row;

	h1 = (unsigned long*) malloc(COLUMN_WEIGHT*sizeof(unsigned long));
	h2 = (unsigned long*) malloc(COLUMN_WEIGHT*sizeof(unsigned long));
	H_first_row = (unsigned long*) malloc(2*COLUMN_WEIGHT*sizeof(unsigned long));
		
	sample_col(h1);
	sample_col(h2);
	create_first_row_from_h1_h2(h1, h2, H_first_row);
	
	for(int i = 0; i<COLUMN_WEIGHT; i++){
		printf("\nh1[%d] = %d",i,h1[i]);
	}
	printf(" ");
	for(int i = 0; i<COLUMN_WEIGHT; i++){
		printf("\nh2[%d] = %d",i,h2[i]);
	}
	
	
	printf(" ");
	for(int i = 0; i<2*COLUMN_WEIGHT; i++){
		printf("\nH[%d] = %d",i,H_first_row[i]);
	}
	
	int *syndrome;
	syndrome = (int*)malloc(CODE_REDUNDANCY*sizeof(int));
		
	for(int t = T_MAX; t>=T_MIN; t+=(-T_STEP)){
		
		//estimate DFR for this value of t
		int num_errors = 0; 
		int num_decodes = 0;
		
		clock_t time_for_bf;
		time_for_bf = clock();
		
		while((num_errors<NUM_ERRORS_MAX)&(num_decodes<NUM_DECODES_MAX)){			
			
			num_decodes ++;
			
			//Sample error vector
			unsigned long *err_support;
			err_support = (unsigned long*) malloc(t*sizeof(unsigned long));			
			sample_error(err_support, t);
			
			//DELETE LATER
			/*
			printf("\ne = ");
			for(int i = 0; i<t; i++){
				printf("%d, ",err_support[i]);
			}*/

			//Compute syndrome
			QC_compute_syndrome(err_support, h1, h2, syndrome, t);
			
			//Decode
			int* error_estimate;
			error_estimate = (int*)malloc(CODE_LENGTH*sizeof(int));
			int ws = qc_bf_max(syndrome, error_estimate, h1, h2, H_first_row, t);
			
			//Check if decoding is ok
			if(ws>0){
				num_errors ++;
				//Update log file
				time_t time_now = time(NULL);
				struct tm tm = *localtime(&time_now);
//				printf("%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  
				fptr_log = fopen(file_log, "a");
				fprintf(fptr_log, "\nt = %d, Num Tx = %d, Num Errors = %d, Current DFR =  %e, (%d-%02d-%02d %02d:%02d:%02d)",t, num_decodes, num_errors, (float)num_errors/(float)num_decodes, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
				fclose(fptr_log);
			}
			
			//update log file
			if((num_decodes%NUM_BACKUP)==0){
				time_t time_now = time(NULL);
				struct tm tm = *localtime(&time_now);
//				printf("%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  
				fptr_log = fopen(file_log, "a");
				fprintf(fptr_log, "\nt = %d, Num Tx = %d, Num Errors = %d, Current DFR =  %e, (%d-%02d-%02d %02d:%02d:%02d)",t, num_decodes, num_errors, (float)num_errors/(float)num_decodes, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
				fclose(fptr_log);
			}
			//true_error[CODE_LENGTH];
			//int decoded_t = 0;
			//for(int i = 0; i< CODE_LENGTH; i++){
			//if(error_estimate[i] == 1){
			//decode_error_support[i]
			//}
			//}
			//}
			free(err_support);
			free(error_estimate);
		}
		
		//print values
		time_for_bf = clock() - time_for_bf; 
		double time_taken = ((double)time_for_bf)/(CLOCKS_PER_SEC*num_decodes); // in seconds 
		float DFR = (float)num_errors/(float)num_decodes;
		printf("\n t = %d, DFR = %e (time for one decode = %f s)", t, DFR, time_taken);
		
		//Update results file
		fptr_out = fopen(file_output, "a");
		fprintf(fptr_out, "(%d, %e)\n",t, (float)num_errors/(float)num_decodes);
		fclose(fptr_out);
	}
	printf("\n");
	/*
    //Compute adjancency matrix
    static unsigned A[CODE_LENGTH*CODE_LENGTH];
	

     	
    compute_A(H_cols, A);
	


    printf("\nComputing A (schoolbook) took %f seconds to execute \n", time_taken); 
	

    printf("\n v = %d, max_value in A = %d",COLUMN_WEIGHT, max_val);
    int t_tillich = COLUMN_WEIGHT /(2*max_val);
    printf("\nt(tillich) = %d\n", t_tillich);
	*/
	
	
	
   return 0;
}
