#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sum; /* shared data between threads */
int product;

/* threads call this function */
void *runner(void *param); 
void *runner2(void *param);

int main(int argc, char *argv[])
{
    pthread_t tid; /* thread identifier */
    pthread_attr_t attr; /* thread attributes */

    pthread_t tid2; /* second thread identifier */
    pthread_attr_t attr2; /* second thread attr */

    /* set the default thread attributes */
    pthread_attr_init(&attr);

    /* create the threads */
    pthread_create(&tid, &attr, runner, argv[1]);
    pthread_create(&tid2, &attr, runner2, argv[1]);


    /* wait for the thread to exit */
    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);

    /* print the sum computed by the thread */
    printf("sum = %d\n", sum);
    printf("prod = %d\n", product);
}

/* The thread will execute in this function */
void *runner(void *param)
{
    int i, upper = atoi(param); /* convert command line argument to integer */

    sum = 0; /* initialize the shared variable */

    /* compute the sum of integers from 1 to the upper limit */
     for (i = 1; i <= upper; i++){
        product += i;
        printf("curr: %d\niter: %d", sum, i);
        usleep(upper / i);
    }
    pthread_exit(0); /* exit the thread */
}

void *runner2(void *param)
{
    int i, n = atoi(param); /* convert command line argument to integer */

    /* initialize the shared variable */
    int product = 1;

    /* compute the product of integers from 1 to n */
    for (i = 1; i <= n; i++){
        product -= 2 * i;
        printf("curr: %d\niter: %d", product, i);
        usleep(20);
    }
    pthread_exit(0); /* exit the thread */
}
