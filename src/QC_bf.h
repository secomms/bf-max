#ifndef __BF_H__
#define __BF_H__

int qc_bf_max(int* syndrome, int* error_estimate, const unsigned long *h1, const unsigned long *h2, const unsigned long *H_first_row, const int num_iter_max);

#endif