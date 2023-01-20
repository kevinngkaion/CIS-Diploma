/*
Author: Kevin Ngkaion
Date: Jan 18, 2023
Description: This program takes the first name and last name from the user as well as a lucky number.
             It then creates a username by taking first char of first name and concatenating the last
             name and lucky number to it before returning the username and lucky number to the user.
COSC315 LAB 1
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getUserInfo(char** uname);

int main(){
    char* username;
    int lucky = getUserInfo(&username);
    printf("The lucky number of user %s is %d.\n", username, lucky);
    free(username);
    return 0;
}

int getUserInfo(char** uname){
    char* fname = (char*)malloc(32*sizeof(char));
    char* lname = (char*)malloc(32*sizeof(char));
    int num;
    printf("Enter your first and last name: ");
    scanf("%s %s", fname, lname);
    printf("Hello %s. Enter your lucky number (from 1 to 99): ", fname);
    scanf("%d", &num);

    //allocate memory for the username
    *uname = (char*)malloc(64*sizeof(char));
    //Set first char of uname to first char of fname
    **uname = *fname;
    //Concat lname to uname
    strcat(*uname, lname);
    char* lucknum = (char*)malloc(8*sizeof(char));
    sprintf(lucknum, "%d", num);
    strcat(*uname, lucknum);

    free(fname);
    free(lname);
    return num;
}