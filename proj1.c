#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RAND_MAX 25000

/* threads call this function */
void *runner(void *param);

/// @brief This structure is used to easily pass information to the individual thread functions.
typedef struct
{
    int *array;
    int len;
} ArrayData;

// HELPER FUNCTIONS

/// @brief Sorts an array of integers in ascending order using bubble sort algorithm.
/// @param intArr The array of integers to be sorted.
/// @param arrLength The length of the array.
void sort(int intArr[], int arrLength)
{
    ;
    int i, j, temp;

    for (i = 0; i < arrLength - 1; i++)
    {
        for (j = 0; j < arrLength - i - 1; j++)
        {
            if (intArr[j] > intArr[j + 1])
            {
                temp = intArr[j];
                intArr[j] = intArr[j + 1];
                intArr[j + 1] = temp;
            }
        }
    }
}

/// @brief This function quickly takes in an array and prints the contents.
/// @param intArray The array to be listed
/// @param arrLength The length of the array
void printer(int intArray[], int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        printf("SLOT %d | %d\n", i + 1, intArray[i]);
    }
}

/// @brief This function quickly fills an array with 0's.
/// @param intArray The array to be cleaned
/// @param arrLength The length of the array
void cleaner(int intArray[], int arrLength)
{
    printf("len: %d\n", arrLength);
    for (int i = 0; i < arrLength; i++)
    {
        intArray[i] = 0;
    }
}

/// @brief This function quickly takes in an array and fills the content with random numbers. Will rewrite array contents.
/// @param intArray The array to be listed
/// @param arrLength The length of the array
void filler(int intArray[], int arrLength)
{
    cleaner(intArray, arrLength);
    for (int i = 0; i < arrLength; i++)
    {
        intArray[i] = rand() % RAND_MAX; // this ensures that if the rand() number is higher than the specified amt, the number will roll over and not be egregiously large.
        // printf("PUT %d AT %d\n", intArray[i], i); test function
    }
}

// MAIN FUNCTIONALITY

/// @brief Function to take two arrays, the size of two arrays, and the intended array to output to and merges the two arrays to be in ascending order.
/// @param arr1 First array
/// @param size1 First array's size
/// @param arr2 Second array
/// @param size2 Second array's size
/// @param merged Array to be merged into.
void merge(int arr1[], int size1, int arr2[], int size2, int merged[])
{

    // init 3 index values
    int index1 = 0;
    int index2 = 0;
    int indexResult = 0;

    // Traverse both arrays at the same time until one is fully processed
    while (index1 < size1 && index2 < size2)
    {
        // if first element is lteq to second element, add first to the result.
        if (arr1[index1] <= arr2[index2])
        {
            merged[indexResult] = arr1[index1];
            index1++;
        }
        // otherwise, do so for the second to the result.
        else
        {
            merged[indexResult] = arr2[index2];
            index2++;
        }
        indexResult++;
    }

    // copy remainder elements after one is completed processing.
    while (index1 < size1)
    {
        merged[indexResult] = arr1[index1];
        index1++;
        indexResult++;
    }

    while (index2 < size2)
    {
        merged[indexResult] = arr2[index2];
        index2++;
        indexResult++;
    }
}

/// @brief the main function loop responsible for taking in user input, taking in the numbers to be sorted,
/// calling the sorting threads, then for the final merge and output to user.
/// @return returns 1 on success, exception or -1 on failure.
int main(int argc, char *argv[])
{

    int original_array_size;

    printf("Enter the n of characters to be input to the array (array size)\n");

    scanf("%d", &original_array_size);

    int sortArray[original_array_size];

    printf("Filling array with random numbers...\n");

    filler(sortArray, original_array_size); // call helper function to randomly gen numbers to be sorted.

    int array1_size = original_array_size / 2;
    int array2_size = original_array_size - array1_size;

    int array1[array1_size], array2[array2_size];

    for (int i = 0; i < array1_size; i++)
    {
        array1[i] = sortArray[i];
    }
    for (int i = array1_size; i < original_array_size; i++)
    {
        array2[i - array1_size] = sortArray[i];
    }

    ArrayData array1_data = {array1, array1_size};
    ArrayData array2_data = {array2, array2_size};

    pthread_t tid;       /* thread identifier */
    pthread_attr_t attr; /* thread attributes */

    pthread_t tid2;       /* second thread identifier */
    pthread_attr_t attr2; /* second thread attr */

    pthread_attr_init(&attr); // initialize both threads
    pthread_attr_init(&attr2);

    printf("Calculating\n");

    pthread_create(&tid, &attr, runner, &array1_data); // create the threads and pass relevant data to them to be calc'd
    pthread_create(&tid2, &attr, runner, &array2_data);

    pthread_join(tid, NULL); // when finished, join threads back to main
    pthread_join(tid2, NULL);

    cleaner(sortArray, original_array_size); // clean out the original array to be used as storage for sorted array. why allocate new memory?

    merge(array1_data.array, array1_size, array2_data.array, array2_size, sortArray); // call the merge helper function to merge two sorted arrays.

    printer(sortArray, original_array_size); // print out the contents of the array.

    return 1; // return with a success code
}

/// @brief each thread is to call this function, just calls bubblesort for each array.
/// @param param struct holding the array data, as well as the length of the array
/// @return void
void *runner(void *param)
{
    ArrayData *data = (ArrayData *)param;
    int *array = data->array;
    int len = data->len;

    sort(array, len);
}
