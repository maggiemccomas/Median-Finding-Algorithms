
# include <stdlib.h>
# include <stdio.h>
# include <time.h>

/**
 * The purpose of this program is to use the quickSort alogirthm to sort through an unordered
 * array and return the kth smallest element in the given array.
 * 
 * Maggie McComas
 */

int size;
int arrLargeQS[10000000];

/**
 * input: array S, int begin, int end
 * output: int pointer (index of the pivot)
 * purpose: the purpose of this function is to put the element at the end of the array
 * into its correct positon in the unordered array.
 */
int split(int S[], int begin, int end){
    int pivot = S[end];
    int pointer = begin;
    int temp = 0;

    for (int i = begin; i < end; i++){
        if (S[i] <= pivot){
            temp = S[pointer];
            S[pointer] = S[i];
            S[i] = temp;
            pointer++;
        }
    }

    temp = S[pointer];
    S[pointer] = S[end];
    S[end] = temp;

    return pointer;
}

/**
 * input: array S, int begin, int end
 * output: the output of the split function, which is: int pointer (index of the pivot)
 * purpose: the purpose of this function is find a random element in the unordered array
 * and move it to the end so it can be used as the pivot when it calls the split function.
 */
int randPivot (int S[], int begin, int end){
    int temp;
    int rPivot = begin + rand() % (end - begin);

    temp = S[rPivot];
    S[rPivot] = S[end];
    S[end] = temp;
 
    return split(S, begin, end);
}

/**
 * input: array S, int start, int end
 * output: none (void function)
 * purpose: the purpose of this function is to recusively sort the given unsorted array. 
 * This function implements the quickSort algorithm that finds a random element and puts it in its correct spot 
 * and then uses the same algorithm on the left and right side of this element to sort them as well.
 */
void sort(int S[], int start, int end){
    if (start < end){
        int pivot = randPivot(S, start, end);

        sort(S, start, pivot - 1);
        sort(S, pivot + 1, end);
    }
}

/**
 * input: array S, int k
 * output: the kth smallest element in array S
 * purpose: the purpose of this function is to call the function sort and supply it with 
 * parameters such as begin and end to help with the quick sort algorithm.
 */
int quickSort(int S[], int k){
    sort(S, 0, size-1);
    return S[k-1];
}

/**
 * input: none
 * output: prints statments to the user
 * purpose: the purpose of this function is to use the quick sort algorithm 
 * implemented in the functions above to find the median of an unsorted array with
 * 10000000 elements. As well as time how long this takes. 
 */
int main(){
    srand(time(NULL));
    clock_t time;
    int ret;
    double time_taken;

    printf("Algorithm 3: Sorting (Quicksort) with 10000000 integers\n");
    printf("\n");
    for (int i = 0; i < 10000000; i++){
        arrLargeQS[i] = rand() % 10000001;
    }
    size = sizeof(arrLargeQS) / sizeof(arrLargeQS[0]);
    int k = 5000000;
    size = size - 1;
    time = clock();
    ret = quickSort(arrLargeQS, k);
    time = clock() - time;
    time_taken = ((double)time)/CLOCKS_PER_SEC;

    printf("The median is: %d\n", ret);
    printf("It took Quickssort() %f seconds to find the median for a random uniformly distributed array with 10000000 integers\n", time_taken);
}