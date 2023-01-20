/*
Author: Kevin Ngkaion
Date: Jan 18, 2023
Description: This program implements a linked list with an insertData function to insert data into the linked list at either the starting node or the ending node.
COSC315 LAB 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char* data;
    struct node* next;
};

// Two functions already implemented
struct node* makeNode(const char* data, struct node* n);
void printll(struct node* n);

// A function you will implement
void insertData(const char* data, struct node** ptrToHead, int location);

int main() {
    struct node* head = NULL, n1, n2;
    head = makeNode("Bob", NULL);

    // head->next = makeNode("Sue", NULL);
    // head->next->next = makeNode("Arya", NULL);
    insertData("Brie", &head, 0);
    printll(head);
    insertData("Jack", &head, 1);
    printll(head);
    insertData("Arya", &head, 1);
    printll(head);
    insertData("Tyrion", &head, 0);
    printll(head);

    return 0;
}

struct node* makeNode(const char* data, struct node* n){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = (char*)malloc((strlen(data)+1) * sizeof(char));
    strcpy(temp->data, data);
    temp->next = n;
    return temp;
}

void printll(struct node* n){
    while(n != NULL && n->next != NULL){
        printf("%s ---> ", n->data);
        n = n->next;
    }
    if(n != NULL){
        printf("%s\n", n->data);
    }
}

void insertData(const char* data, struct node** ptrToHead, int location){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    struct node* temp = *ptrToHead;
    // allocate memory for the new data string and copy to the newNode->data
    newNode->data = (char*)malloc((strlen(data)+1) * sizeof(char));
    strcpy(newNode->data, data);
    //case if there are no nodes on the linked list yet
    if(temp == NULL){
        newNode->next = NULL;
        *ptrToHead = newNode;
    } else { // do this if there is already a node that ptrToHead points to
        switch (location) {
        case 0: // add to start of linked list
            newNode->next = *ptrToHead;
            *ptrToHead = newNode;
            break;
        case 1: // add to end of linked list
            // traverse to the end of the linked list
            while (temp != NULL && temp->next != NULL){
                temp = temp->next;
            }
            temp->next = newNode;
            break;
        }
    }
}