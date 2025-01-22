#include "params.h"

void create_first_row_from_h1_h2(unsigned long *h1, unsigned long *h2, unsigned long *H_first_row){
		
	//Create the support of the first row of H 
	int num_ones = 0;
	
	if(h1[0]==0){
		H_first_row[num_ones] = 0;
		num_ones ++;
	}
	for(int i = num_ones; i< COLUMN_WEIGHT; i++){
		H_first_row[num_ones] = (CODE_REDUNDANCY-h1[COLUMN_WEIGHT-1-i]);
		num_ones ++;
	}
	
	if(h2[0]==0){
		H_first_row[num_ones] = 0;
		num_ones ++;
	}
	for(int i = 0; i< COLUMN_WEIGHT; i++){
		H_first_row[num_ones] = CODE_REDUNDANCY+(CODE_REDUNDANCY-h2[COLUMN_WEIGHT-1-i]);
		num_ones ++;
	}
}

void QC_compute_syndrome(unsigned long *err_support, unsigned long *h1, unsigned long *h2, unsigned int *syndrome, const int t){
	
	//assign all syndrome values to 0
	for(int i = 0;i < CODE_REDUNDANCY; i++){
		syndrome[i] = 0;
	}
	
	//start modifying syndrome
	for(int i = 0; i < t; i++){
		int pos = err_support[i];
		if (pos < CODE_REDUNDANCY){
			for(int j = 0; j<COLUMN_WEIGHT; j++){
				unsigned long pos_to_flip = (h1[j]+pos)%CODE_REDUNDANCY;
				syndrome[pos_to_flip] = syndrome[pos_to_flip]^1;
			}
		}else{
			for(int j = 0; j<COLUMN_WEIGHT; j++){
				unsigned long pos_to_flip = (h2[j]+pos)%CODE_REDUNDANCY;
				syndrome[pos_to_flip] = syndrome[pos_to_flip]^1;
			}
		}
	}
}