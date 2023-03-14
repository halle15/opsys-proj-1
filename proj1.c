#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



/* threads call this function */
void *runner(void *param); 
void *runner2(void *param);

void printer(int intArray[], int arrLength)
{
    printf("len: %d\n", arrLength);
    for(int i = 0; i < arrLength; i++){
       

        printf("SLOT %d | %d\n", i + 1, intArray[i]);
    }
}

int main(int argc, char *argv[])
{

    int original_array_size;
   
    printf("Enter the n of characters to be input to the array (array size)\n");

    scanf("%d", &original_array_size);

    int toSortArray[original_array_size];

    for(int i = 0; i < original_array_size; i++){
        scanf("%d", &toSortArray[i]);
    }
   
    int array1_size = original_array_size / 2;
    int array2_size = original_array_size - array1_size;

    int array1[array1_size], array2[array2_size];

    for (int i = 0; i < array1_size; i++){
        array1[i] = toSortArray[i];
    }
    for (int i = array1_size; i < original_array_size; i++){
        array2[i - array1_size] = toSortArray[i];
    }
   

    printer(array1, array1_size);
    printf("SECOND ARRAY\n");
    printer(array2, array2_size);

    // create two threads w attrs

    // create/find a sorting function for the array

    // figure out how to join the remaining two arrays together.


    pthread_t tid; /* thread identifier */
    pthread_attr_t attr; /* thread attributes */

    pthread_t tid2; /* second thread identifier */
    pthread_attr_t attr2; /* second thread attr */




    return 0;
}