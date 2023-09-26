# include <stdlib.h>
# include <stdio.h>
# include <time.h>

/**
 * The purpose of this program is to implement the randomized slection algorithm 
 * and return the kth smallest element in a given unordered array.
 * 
 * Maggie McComas
 */

int size;
int arrLargeRS[10000000];

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
 * input: array S, int begin, int end, int k
 * output: the kth smallest element in the array. It is a resursive function so other outputs 
 * include recusively calling itself until it returns the kth smallest element in the array.
 * purpose: the purpose of this function is to recusively cycle through random pivots until
 * it selects the kth smallest element in the array and returns it.
 */
int randSelect(int S[], int start, int end, int k){
      if (start == end){
        return S[start];
    }
    
    if (k == 0){
        return -1;
    }

    if (start < end){
        int pivot = randPivot(S, start, end);
        int index = pivot - start + 1;
        
        if (index == k){
            return S[pivot];
        }
        else if (k < index){
            return randSelect(S, start, pivot - 1, k);
        }
        else{
            return randSelect(S, pivot + 1, end, k - index);
        }
    }

    return -1;
}

/**
 * input: array S, int k
 * output: the kth smallest element in array S
 * purpose: the purpose of this function is to call the function randSelect and supply it with 
 * parameters such as begin and end to help with the randomized selection algorithm.
 */
int randomSelection(int S[], int k){
    int ret = randSelect(S, 0, size - 1, k);
    return ret;
}

/**
 * input: none
 * output: prints statments to the user
 * purpose: the purpose of this function is to use the randomized selection algorithm 
 * implemented in the functions above to find the median of an unsorted array with
 * 10000000 elements. As well as time how long this takes. 
 */
int main(){
    srand(time(NULL));
    clock_t time;
    double time_taken;

    printf("Algorithm 1: Randomized Selection with 10000000 integers\n");
    printf("\n");
    for (int i = 0; i < 10000000; i++){
        arrLargeRS[i] = rand() % 10000001;
    }
    size = sizeof(arrLargeRS) / sizeof(arrLargeRS[0]);
    int k = 5000000;
    time = clock();
    int ret = randomSelection(arrLargeRS, k);
    time = clock() - time;
    time_taken = ((double)time)/CLOCKS_PER_SEC;

    printf("The median is: %d\n", ret);
    printf("It took randomized selection %f seconds to find the median for a random uniformly distributed array with 10000000 integers\n", time_taken);
}