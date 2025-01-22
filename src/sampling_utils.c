#include "sampling_utils.h"
#include "params.h"
#include <stdlib.h>

void sample_col(unsigned long col_support[COLUMN_WEIGHT]){

    //assign first position
    unsigned long pos = rand()%CODE_REDUNDANCY;
    col_support[0] = pos;
    int num_found = 1;

    while(num_found < COLUMN_WEIGHT){
        pos = rand()%CODE_REDUNDANCY;

        int flag_duplicate = 0;
        for(int i = 0;i<num_found;i++){
            if(col_support[i] == pos){ 
                flag_duplicate = 1;
            }
        }
        if (flag_duplicate == 0){
            col_support[num_found] = pos;
            num_found ++;
        }
    }
	
	//sort the vector
	mergeSort(col_support, 0, COLUMN_WEIGHT-1);
}

void sample_error(unsigned long *err_support, int t){

    //assign first position
    unsigned long pos = rand()%(2*CODE_REDUNDANCY);
    err_support[0] = pos;
    int num_found = 1;

    while(num_found < t){
        pos = rand()%(2*CODE_REDUNDANCY);

        int flag_duplicate = 0;
        for(int i = 0;i<num_found;i++){
            if(err_support[i] == pos){ 
                flag_duplicate = 1;
            }
        }
        if (flag_duplicate == 0){
            err_support[num_found] = pos;
            num_found ++;
        }
    }
	
	//sort the vector
	mergeSort(err_support, 0, t-1);
}

// Function to merge two halves of the array
void merge(unsigned long arr[], int l, int m, int r) {
    int n1 = m - l + 1; // Size of the left subarray
    int n2 = r - m;     // Size of the right subarray

    unsigned long L[n1], R[n2];   // Temporary arrays to hold the two halves

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l; // Initial indices of the subarrays and merged array

    // Merge the temporary arrays back into arr[l..r]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to implement MergeSort
void mergeSort(unsigned long *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2; // Find the middle point

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

//Binary search
int binarySearch(const unsigned long *array, unsigned long x, int low, int high) {
  // Repeat until the pointers low and high meet each other
  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (x == array[mid])
      return mid;

    if (x > array[mid])
      low = mid + 1;

    else
      high = mid - 1;
  }

  return -1;
}