#ifndef __PARAMS_H__
#define __PARAMS_H__

#define CODE_LENGTH       4006 // code length
#define CODE_REDUNDANCY   2003 // code redundancy
#define COLUMN_WEIGHT     35 // column weight

//Parameters for simulation
#define T_MIN  2 //minimum error weight to consider
#define T_MAX  100 //maximum error wegith to consider
#define T_STEP 1 //difference between two consectuvie simulated weights

#define NUM_DECODES_MAX 10000000 //max number of tests for each weight
#define NUM_ERRORS_MAX 100 //max number of errors for each weight
#define NUM_BACKUP 100000//number of decodes to print in log file

#define INITIAL_SEED 0 //seed for initializing PRNG


#endif
