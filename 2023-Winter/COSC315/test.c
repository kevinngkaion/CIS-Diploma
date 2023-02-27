#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    printf("%d\n", fork());
    if(!fork()){
        printf("This is in the child: %d\n", fork());
    }
    sleep(1);
    return 0;
}