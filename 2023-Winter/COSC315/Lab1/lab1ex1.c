#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(){
    int input = 0;
    int min = INT_MAX;
    int max = 0;
    int sum = 0;
    int count = 0;
    float average = 0;
    int variance = 0;

    // TODO: Use malloc to dynamically create an array and resize this array when it gets full by copying it to a new 
    // array that is twice the size
    
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
            count++;
        }
    }

    //Calculate the average
    average = (double)sum/count;

    printf("The sum of %d integers is \n", count);
    printf("The Maximum: %5d \n", max);
    printf("The Minimum: %5d \n", min);
    printf("The Average: %6.3f \n", average);
}
