/*
Author: Kevin Ngkaion
Date: Jan 18, 2023
Description: This program takes integers from the user as input and calculates the
             average, min, max, and variance of the numbers entered.
COSC315 LAB 1
*/
//TODO: Create username for person:
//      1. Get first char in fname
/*      2. Concat to lname
        3. Concat favnumber
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getUserInfo(char** uname);

int main(){
    char* username;
    int lucky = getUserInfo(&username);
    printf("The lucky number of user %s is %d.\n", username, lucky);
    return 0;
}

int getUserInfo(char** uname){
    char* fname = (char*)malloc(32*sizeof(char));
    char* lname = (char*)malloc(32*sizeof(char));
    int num;
    printf("Enter your first and last name: ");
    scanf("%s %s", fname, lname);
    printf("Hello %s. Enter your lucky number (from 1 to 99):", fname);
    scanf("%d", &num);
    *uname = fname;
    return num;
}