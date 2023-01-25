/*
Author: Kevin Ngkaion
Date: Jan 18, 2023
Description: This program takes integers from the user as input and calculates the
             average, min, max, and variance of the numbers entered.
COSC315 LAB 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int main(){
    int input = 0;
    int min = INT_MAX;
    int max = 0;
    int sum = 0;
    int count = 0;
    double average = 0;
    double variance = 0;
    int size = 1; //Initial size of the array. This will be updated when I resize the array
    int* nums = (int*)malloc(size * sizeof(int));
    
    //loop until user provides stop input
    while (input != -1){
        //prompt user for input
        printf("Enter a positive integer (-1 to stop): ");
        scanf("%d", &input);
        //only execute this if user has not input exit code
        if (input != -1){
            if (input < min){
                min = input;
            }
            if (input > max){
                max = input;
            }
            sum += input;
            // check if the array needs to be resized. If so, resize the array by allocating new memory.
            if (count+1 == size){
                //Double the size of the array
                size = size * 2;
                //create temp pointer and point it to new malloc
                int* temp = (int*)malloc(size * sizeof(int));
                memcpy(temp, nums, (count + 1) * sizeof(nums[0]));
                free(nums);
                nums = temp;
                temp = 0;
            }
            nums[count] = input;
            count++;
        }
    }

    //Calculate the average
    if(count > 0){
        average = (double)sum/count;
    }

    //Calculate the variance
    double ssd = 0;
    int i;
    for(i = 0; i < count; i++){
        ssd = ssd + ((nums[i] - average) * (nums[i] - average));
    }
    if(count == 1){
        variance = 0;
    } else {
        variance = ssd / (count - 1);
    }

    printf("The sum of %d integers is %d\n", count, sum);
    printf("The Maximum: %6d \n", max);
    printf("The Minimum: %6d \n", min);
    printf("The Average: %10.3f \n", average);
    printf("The Variance: %7.1f \n", variance);
    free(nums);
    return 0;
}
