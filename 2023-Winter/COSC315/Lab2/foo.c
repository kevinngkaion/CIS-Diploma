#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    // Question 5
        char* buff = (char*)malloc(128*sizeof(char));
        int pid, p1[2], p2[2];
        pipe(p1);
        pipe(p2);
        pid = fork();
        if(pid == 0){
            //reading parent's message
            read(p1[0], buff, 128);
            printf("Parent said: %s\n",buff);
            sprintf(buff, "%s", "Almost. How did the Vikings send secret message?");
            //writing child's response
            write(p2[1], buff, strlen(buff)+1);
            //reading parent's response
            read(p1[0], buff, 128);
            printf("Parent response: %s\n", buff);
            return 0;
        }
        sprintf(buff, "%s", "Have you finished your history homework?");
        //parent writing initial message
        write(p1[1], buff, strlen(buff)+1);
        //reading child's response
        read(p2[0], buff, 128);
        printf("Child response: %s\n", buff);
        sprintf(buff, "%s", "I think it was by Norse Code");
        //writing response back to child
        write(p1[1], buff, strlen(buff)+1);
        return 0;
    }

// int main() {
//     // Question 7
//     int x = 88888;
//     int* z = &x;
//     printf("x = %d, Address of x = %p\n\n", x, &x);
//     if(fork() == 0){
//         *z = 12345;
//         printf("In child: x = %d, Address of x = %p\n", x, &x);
//         printf("The child process is ending.\n\n");
//         return 0;
//     }
//     wait(NULL);
//     printf("In parent: x = %d, Address of x = %p\n", x, &x);
//     printf("The parent process is ending.\n\n");
//     return 0;
// }