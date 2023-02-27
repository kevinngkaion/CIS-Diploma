#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int arrSize(int arr[]){
    printf("Inside function\n");
    int size = sizeof(arr);
    printf("Size of arr: %d\n\n", size);
    return 0;
}

int main(){
    int arr[10] = {1,2,3,4,5};
    int sizeB = sizeof(arr);
    int size = sizeB/sizeof(arr[0]);
    printf("Size of arr in bytes: %d\nSize of arr: %d\n\n", sizeB, size);
    arrSize(arr);
}