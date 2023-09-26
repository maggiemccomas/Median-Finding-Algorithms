
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <math.h>

/**
 * The purpose of this program is to use three different algorithms to find the median,
 * or more generally for selection of the k'th smallest element in an unordered array.
 * 
 * Maggie McComas
 */

int size; int QS;

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
 * input: array S, int num, int val
 * output: the output of the split function, which is: int pointer (index of the pivot)
 * purpose: the purpose of this function is find the index of the median element in the unordered array
 * and move it to the end so it can be used as the pivot when it calls the split function.
 */
int medPivot (int S[], int num, int val){
	for (int i = 0; i < num; i++){
		if(S[i] == val){
			S[i] = S[num-1];
			S[num-1] = val;
		}
	}

	int ret = split(S, 0, num-1);

    return ret;
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
 * input: array S, int start, int end
 * output: none (void function)
 * purpose: the purpose of this function is to recusively sort the given unsorted array. 
 * This function implements the quickSort algorithm that finds a random element and puts it in its correct spot 
 * and then uses the same algorithm on the left and right side of this element to sort them as well.
 */
void sort(int S[], int start, int end){
    if (start < end){
        int pivot;
        if (QS == 0){
            pivot = split(S, start, end);
        }
        else {
            pivot = randPivot(S, start, end);
        }

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
 * input: array S, int k, int num
 * output: the kth smallest element in the array. It is a resursive function so other outputs 
 * include recusively calling itself, and functitions such as sort, until it returns the kth smallest element 
 * in the array.
 * purpose: the purpose of this function is to implement the median of medians algorithm which takes an unordered arrary
 * and finds the median of 5 elements in the array. From these medians, it finds the median of the medians and then compares
 * that to the given k. If k is less than or greater then the index of the median of medians
 *  it recusively calls itself with either the elemets to the left or right of the median of medians. 
 */
int MoM(int S[], int k, int num){
	if (num < 11){
		sort(S, 0, num - 1);
		return S[k-1];
	}

	int numMeds = 0;
	int medOfMeds;
	int index;

	for (int i = 0; i < num; i +=5){
		int pointer;
		int temp;

		if (4 < num-i){
			pointer = 4;
		}
		else{
			pointer = num - i;
		}

		sort(S, i, pointer);
		temp = S[i/5];
		S[i/5] = S[i + pointer/2];
		S[i + pointer/2] = temp;
		numMeds++;
	}

	if (numMeds < 2){
		medOfMeds = S[0];
	}
	else{
		medOfMeds = MoM(S, numMeds/2, numMeds);
	}

	index = medPivot(S, num, medOfMeds);

	if (k == index){
		return medOfMeds;
	}
	else if (k < index){
		return MoM(S, k, index);
	}
	else{
		return MoM(S + index, k - index, num - index);
	}
}

/**
 * input: array S, int k
 * output: the kth smallest element in array S
 * purpose: the purpose of this function is to call the function MoM and supply it with 
 * the additional parameter num(which is just size) to help with the median of medians algorithm.
 */
int medianOfMedians(int S[], int k){
    int ret = MoM(S, k, size);
    return ret;
}

/**
 * input: none
 * output: prints statments to the user
 * purpose: the purpose of this function is to use the above implemented algorithms (randomized selection,
 * median of medians, and quicksort) to find the median of an unsorted array with. As well as time how long this takes. 
 */
int main(){
    srand(time(NULL));
    clock_t time;
    int arr[20] = {7, 2, 4, 6, 9, 11, 2, 6, 10, 6, 15, 6, 14, 2, 7, 5, 13, 9, 12, 15};
    size = sizeof(arr) / sizeof(arr[0]);
    int k = 10;
    int ret;
    double time_taken;

    printf("\n");
    printf("Algorithm 1: Randomized Selection\n");
    printf("Find the median of array: ");
    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    time = clock();
    ret = randomSelection(arr, k);
    time = clock() - time;
    time_taken = ((double)time)/CLOCKS_PER_SEC;

    printf("The median is: %d\n", ret);
    printf("It took randomized selection %f seconds to find the median of this array\n", time_taken);
    printf("\n");
    printf("\n");

    printf("Algorithm 2: Deterministic Selection (Median of Medians)\n");
    QS = 0;
    int arrMOM[20] = {7, 2, 4, 6, 9, 11, 2, 6, 10, 6, 15, 6, 14, 2, 7, 5, 13, 9, 12, 15};
    size = sizeof(arrMOM) / sizeof(arrMOM[0]);
    printf("Find the median of array: ");
    for (int i = 0; i < size; i++){
        printf("%d ", arrMOM[i]);
    }
    printf("\n");
    k = 10;
    time = clock();
    ret = medianOfMedians(arrMOM, k);
    time = clock() - time;
    time_taken = ((double)time)/CLOCKS_PER_SEC;

    printf("The median is: %d\n", ret);
    printf("It took the median of medians algorithm %f seconds to find the median of this array\n", time_taken);
    printf("\n");
    printf("\n");

    printf("Algorithm 3: Sorting (Quicksort)\n");
    QS = 1;
    int arrQS[20] = {7, 2, 4, 6, 9, 11, 2, 6, 10, 6, 15, 6, 14, 2, 7, 5, 13, 9, 12, 15};
    size = sizeof(arrQS) / sizeof(arrQS[0]);
    printf("Find the median of array: ");
    for (int i = 0; i < size; i++){
        printf("%d ", arrQS[i]);
    }
    printf("\n");
    k = 10;
    size = size - 1;
    time = clock();
    quickSort(arrQS, k);
    time = clock() - time;
    time_taken = ((double)time)/CLOCKS_PER_SEC;

    printf("The median is: %d\n", arrQS[k-1]);
    printf("It took Quickssort() %f seconds to find the median of this array\n", time_taken);   
}

