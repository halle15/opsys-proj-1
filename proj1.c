#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/* threads call this function */
void *runner(void *param); 
void *runner2(void *param);

int printer(int intArray[], int arrayLength){
    for(int i = 0; i < arrayLength; i++){
        printf("SLOT %d | %d\n", i + 1, intArray[i]);
    }
}

int main(int argc, char *argv[])
{

    int array_size;
    int toSortArray[array_size];


    printf("Enter the n of characters to be input to the array (array size)\n");

    scanf("%d", &array_size);


    for(int i = 0; i < array_size; i++){
        scanf("%d", &toSortArray[i]);
    }
   
    printer(toSortArray, array_size);
   
    int midpoint = array_size/2;

    int array1[midpoint + 1];
    int array2[midpoint + 2];
    
    

    // create two threads w attrs

    // create/find a sorting function for the array

    // figure out how to join the remaining two arrays together.


    pthread_t tid; /* thread identifier */
    pthread_attr_t attr; /* thread attributes */

    pthread_t tid2; /* second thread identifier */
    pthread_attr_t attr2; /* second thread attr */




    return 0;
}