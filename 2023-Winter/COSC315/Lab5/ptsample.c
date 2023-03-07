/* ptsample.c -- Sample of threads
   Solaris compilation:  gcc ptsample.c -lpthread
   Solaris run:          a.out
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // For sleep()

void thread1();                      /* function prototypes */
void thread2();                      /* function prototypes */
pthread_t tid1, tid2;                /* The thread ids for each thread */

/*************************************************************************/

int main () {

  // Note that since thread1 waits for thread2, thread2 must be created
  //      before thread1. Otherwise the tid2 variable may not be
  //      valid in the pthread_join(tid2, NULL) call in thread2.

  pthread_create(&tid2, NULL, (void *)thread2, NULL);
  pthread_create(&tid1, NULL, (void *)thread1, NULL);

  printf("Main thread running\n");
  pthread_join(tid1, NULL);          /* main thread waits for thread1 */
  printf("Main thread running after t1 finished\n");
  return 0;
}

/*************************************************************************/

void thread1() {
  int i;
  printf("Thread 1 begins\n");
  pthread_join(tid2, NULL);          /* This thread waits for thread2 */
  sleep(1);                          /* Represents a slow operation */
  printf("Thread 1 finished\n");
}

/*************************************************************************/

void thread2() {
  int i;
  printf("Thread 2 begins\n");
  sleep(1);                          /* Represents a slow operation */
  printf("Thread 2 finished\n");
}

/*************************************************************************/
