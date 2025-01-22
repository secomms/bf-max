#ifndef __LDPC_UTILS_H__
#define __LDPC_UTILS_H__

#include <stdio.h>
#include <string.h>
#include "params.h"
#include "sampling_utils.h"


int gen_H(unsigned long *H_cols, int *row_weights);

void write_H(unsigned long H_cols[COLUMN_WEIGHT*CODE_LENGTH]);

void compute_H_row_supports(const unsigned long *H_cols, const int max_row_weight, unsigned long *H_rows);

void compute_syndrome(unsigned long *err_support, unsigned long *H_cols, unsigned int *syndrome, const int t);

#endif
