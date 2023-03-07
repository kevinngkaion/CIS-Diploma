/*
Author: Kevin Ngkaion
OC#: 300325759
COSC-315 Lab 5
This program solves the equation below with threads using the inherent parallelism of the problem:
    (((a + b) / 4) ^ c) + (d / 2) - ((3 * a) + (4 * e / b))
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// function prototypes
void thread1();
void thread2();
void thread3();
pthread_t tid1, tid2, tid3;     // thread id for each thread

int main(int argc, char* args[]){
    // init variables
    double a, b, c, d, e, answer;
    double* res;
    double abc[3];

    // assign values to variables
    a = atof(args[1]);
    b = atof(args[2]);
    c = atof(args[3]);
    abc[0] = a; abc[1] = b; abc[2] = c; // storing a, b, c in the array to pass to thread 3
    d = atof(args[4]);
    e = atof(args[5]); 

    // creating threads. the last arg is the arg to pass to the thread
    pthread_create(&tid1, NULL, (void*)thread1, (void*) &a);
    pthread_create(&tid2, NULL, (void*) thread2, (void*) &d);
    pthread_create(&tid3, NULL, (void*) thread3, (void*)abc); //passing an array here

    //perform calculation for 4 * e / b
    answer = e * 4;
    answer /= b;
    //get result from first thread
    pthread_join(tid1, (void**)&res);
    //do next cal with the res of first thread
    answer += *res;
    //get result from thread3
    pthread_join(tid3, (void**)&res);
    //do rest of the calc
    answer = *res - answer;
    printf("(((%0.1f + %0.1f) / 4) ^ %0.1f + %0.1f / 2) - (3 * %0.1f + (4 * %0.1f / %0.1f)) = %0.3f\n", a, b, c, d, a, e, b, answer);

    return 0;
}

// this thread is a * 3
void thread1(void* arg){
    double* a = (double*)malloc(sizeof(double));
    *a = *(double*)arg;
    *a *= 3;
    pthread_exit((void*)a);
    free(a);
}

// this thread is d / 2. passing the result of this to thread 3
void thread2(void* arg){
    double* d = (double*)malloc(sizeof(double));
    *d = *(double*) arg;
    *d /= 2;
    pthread_exit((void*)d);
    free(d);
}

// this is ((a + b) / 4)^c. it takes the result of thread 2.
void thread3(void* arg){
    double* abc = (double*)arg;
    double* res = (double*)malloc(sizeof(double));
    double* d = (double*)malloc(sizeof(double));
    *res = abc[0] + abc[1];
    *res /= 4;
    *res = pow(*res, abc[2]);
    //getting result from thread2.
    pthread_join(tid2, (void**)&d);
    *res += *d;
    pthread_exit((void*)res);
    free(res);
}