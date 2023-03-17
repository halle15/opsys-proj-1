#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* threads call this function */
void *runner(void *param);
void *runner1(void *param);

/// @brief this structure is used to easily pass information to the individual thread functions.
typedef struct
{
    int *array;
    int len;
} ArrayData;

void sort(int intArr[], int arrLength){

   int i, j, temp; 
   
   for(i=0; i< arrLength-1; i++){
        for(j=0; j<arrLength-i-1; j++){
            if(intArr[j] > intArr[j+1]){
                temp = intArr[j];
                intArr[j] = intArr[j+1];
                intArr[j+1] = temp;
            }
        }
   }

}

/// @brief this function quickly takes in an array and prints the contents.
/// @param intArray the array to be listed
/// @param arrLength the length of the array
void printer(int intArray[], int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        printf("SLOT %d | %d\n", i + 1, intArray[i]);
    }
}

/// @brief this function quickly fills an array with 0's.
/// @param intArray the array to be cleaned
/// @param arrLength the length of the array
void cleaner(int intArray[], int arrLength)
{
    printf("len: %d\n", arrLength);
    for (int i = 0; i < arrLength; i++)
    {
        intArray[i] = 0;
    }
}

/// @brief function to take two arrays, the size of two arrays, and the intended array to output to and merges the two arrays to be in ascending order.
/// @param arr1 first array
/// @param size1 first array's size
/// @param arr2 second array
/// @param size2 second array's size
/// @param merged array to be merged into.
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

    for (int i = 0; i < original_array_size; i++)
    {
        scanf("%d", &sortArray[i]);
    }

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

    pthread_attr_init(&attr);
    pthread_attr_init(&attr2);

    printf("Calculating\n");

    pthread_create(&tid, &attr, runner, &array1_data);
    pthread_create(&tid2, &attr, runner, &array2_data);

    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);

    cleaner(sortArray, original_array_size);

    merge(array1_data.array, array1_size, array2_data.array, array2_size, sortArray);

    printer(sortArray, original_array_size);

    return 0;
}

/// @brief
/// @param param
/// @return
void *runner(void *param)
{
    ArrayData *data = (ArrayData *)param;
    int *array = data->array;
    int len = data->len;

    sort(array, len);    
}
