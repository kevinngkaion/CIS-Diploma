/*
Author: Kevin Ngkaion
OC#: 300325759
COSC-315 Lab 3
This program solves the equation below using forks, pipes, and concurrency using the inherent parallelism of the problem:
    (((a + b) / 4) ^ c) + (d / 2) - ((3 * a) + (4 * e / b))
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char* args[]){
    // initialize variables
    double a, b, c, d, e, answer, t1, t2, t3;
    int p1[2], p2[2], p3[2];
    int bufsize;

    // assign values to variables
    a = atof(args[1]);
    b = atof(args[2]);
    c = atof(args[3]);
    d = atof(args[4]);
    e = atof(args[5]);
    
    bufsize = sizeof(double); // size of data to be piped
    pipe(p1); pipe(p2); pipe(p3); // set up pipes

    if(!fork()){ // 0 == false in c. !fork() means if fork returns a 0 which what the child will return
        // this is the child1 code
        t1 = a + b;
        t1 /= 4;
        t1 = pow(t1, c);
        sleep(1);
        write(p1[1], &t1, bufsize);
        return 0;
    }

    // code after this will run in parent only
    if(!fork()){ // create child2
        double t4, t5; // declare new variables
        if(!fork()){ // child3
            t4 = 3 * a;
            sleep(1);
            write(p3[1], &t4, bufsize);

            return 0;
        }
        // this is child2 code
        t5 = 4 * e;
        t5 /= b;
        sleep(1);
        read(p3[0], &t4, bufsize);
        t3 = t4 + t5;
        sleep(1);
        write(p2[1], &t3, bufsize);
        
        return 0;
    }

    // back to parent code
    read(p1[0], &t1, bufsize);
    t2 = d / 2;
    sleep(1);
    read(p2[0], &t3, bufsize);
    answer = t1 + t2;
    sleep(1);
    answer -= t3;
    sleep(1);

    printf("(((%0.1f + %0.1f) / 4) ^ %0.1f + %0.1f / 2) - (3 * %0.1f + (4 * %0.1f / %0.1f)) = %0.3f\n", a, b, c, d, a, e, b, answer);

    return 0;
}