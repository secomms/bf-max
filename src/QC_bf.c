#include "QC_bf.h"
#include "params.h"
#include <stdlib.h>

int qc_bf_max(int* syndrome, int* error_estimate, const unsigned long *h1, const unsigned long *h2, const unsigned long *H_first_row, const int num_iter_max){
	
	//Set to 0 error estimate
	for(int i = 0; i<CODE_LENGTH;i++){
		error_estimate[i] = 0;
	}
	
	//Compute counters for the first time
	int counters[CODE_LENGTH];
	
	//Counters for the first part
	for(int i = 0; i<CODE_REDUNDANCY;i++){
		
		//compute i-th counter
		counters[i] = 0;
		
		for(int j = 0; j<COLUMN_WEIGHT; j++){
			unsigned long pos = (h1[j]+i)%CODE_REDUNDANCY;
			counters[i]+=syndrome[pos];
		}
	}
	
	//Counters for the second part
	for(int i = 0; i<CODE_REDUNDANCY;i++){
		
		//compute i-th counter
		counters[i+CODE_REDUNDANCY] = 0;
		
		for(int j = 0; j<COLUMN_WEIGHT; j++){
			unsigned long pos = (h2[j]+i)%CODE_REDUNDANCY;
			counters[CODE_REDUNDANCY + i]+=syndrome[pos];
		}
	}
	
	//Start looping
	int num_iter = 0;
	int ws = 0; 
	for (int i = 0; i<CODE_REDUNDANCY; i++){
		ws += syndrome[i];
	}
	
	while((num_iter < num_iter_max)&(ws!=0)){
		
		num_iter ++;
		
		//Find max counter
		int max_counter = 0;
		int pos_max[CODE_LENGTH]; //array containing indices of positions with max counter
		int num_max = 0; //number of positions with max counter
		for(int i = 0; i<CODE_LENGTH; i++){
			if(counters[i]>max_counter){
				max_counter = counters[i];
				
				//reset counter of positions with max counter
				pos_max[0] = i;
				num_max = 1;
			}
			if(counters[i] == max_counter){
				pos_max[num_max] = i;
				num_max ++;
			}
		}
		
		//Select at random a position to flip
		int pos = rand()%num_max;
		int pos_flip = pos_max[pos];
		
//		printf("\nflipping pos = %d (out of %d), counter = %d",pos_flip, num_max, max_counter);
		//printf("\n");
		
		//Flip position
		error_estimate[pos_flip] = error_estimate[pos_flip] ^ 1;
		
		//Update syndrome and counters
		for(int i = 0; i<COLUMN_WEIGHT; i++){
			unsigned long row_index = 0;
			if (pos_flip < CODE_REDUNDANCY){
				row_index = (h1[i]+pos_flip)%CODE_REDUNDANCY;
			}else{
				row_index = (h2[i]+pos_flip)%CODE_REDUNDANCY;
			}
			
			//update syndrome
			syndrome[row_index] = syndrome[row_index]^1;
			
			int d = 1;
			if(syndrome[row_index] == 0){
				d = -1;
			}
			
			//update all counters in which bit in position row_index participates
			for(int j = 0; j < 2*COLUMN_WEIGHT; j++){
				//update counters
				unsigned long ell = (H_first_row[j]/CODE_REDUNDANCY)*CODE_REDUNDANCY+(H_first_row[j]+row_index)%CODE_REDUNDANCY;
				counters[ell] += d;
			}
		}
		
		//Recompute syndrome weight
		ws = 0; 
		for (int i = 0; i<CODE_REDUNDANCY; i++){
			ws += syndrome[i];
		}
	}

	
	return ws;
}