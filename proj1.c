#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* threads call this function */
void *runner(void *param);
void *runner2(void *param);

typedef struct
{
    int *array;
    int len;
} ArrayData;

int cmpfnc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void printer(int intArray[], int arrLength)
{
    printf("len: %d\n", arrLength);
    for (int i = 0; i < arrLength; i++)
    {

        printf("SLOT %d | %d\n", i + 1, intArray[i]);
    }
}

int main(int argc, char *argv[])
{

    int original_array_size;

    printf("Enter the n of characters to be input to the array (array size)\n");

    scanf("%d", &original_array_size);

    int toSortArray[original_array_size];

    for (int i = 0; i < original_array_size; i++)
    {
        scanf("%d", &toSortArray[i]);
    }

    int array1_size = original_array_size / 2;
    int array2_size = original_array_size - array1_size;

    int array1[array1_size], array2[array2_size];

    for (int i = 0; i < array1_size; i++)
    {
        array1[i] = toSortArray[i];
    }
    for (int i = array1_size; i < original_array_size; i++)
    {
        array2[i - array1_size] = toSortArray[i];
    }

    ArrayData array1_data = {array1, array1_size};
    ArrayData array2_data = {array2, array2_size};

    printer(array1, array1_size);
    printf("SECOND ARRAY\n");
    printer(array2, array2_size);

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

    printer(array1_data.array, array1_size);
    printer(array2_data.array, array2_size);

    // create two threads w attrs

    // create/find a sorting function for the array

    // figure out how to join the remaining two arrays together.

    return 0;
}

void *runner(void *param)
{
    ArrayData *data = (ArrayData *) param;
    int *array = data->array;
    int len = data->len;

    qsort(array, len, sizeof(int), cmpfnc);
}
