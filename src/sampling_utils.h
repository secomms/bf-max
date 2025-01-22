#ifndef __SAMPLING_UTILS_H__
#define __SAMPLING_UTILS_H__
#include "params.h"

void merge(unsigned long *arr, int l, int m, int r);

void mergeSort(unsigned long *arr, int l, int r);

void sample_col(unsigned long col_support[COLUMN_WEIGHT]);

void sample_error(unsigned long err_support[], int t);

int binarySearch(const unsigned long *array, unsigned long x, int low, int high);

#endif
