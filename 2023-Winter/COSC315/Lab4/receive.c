/* receive.c -- socket demo program, which acts as a message server */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define TRUE 1
struct sockaddr saddr;
int s, rfd, ch;
FILE *rf;
char username[15];
char remString[50];
int main() {
    umask(0);
    strcpy(username, getenv("LOGNAME"));
    strcpy(saddr.sa_data, "/tmp/#");
    strcat(saddr.sa_data, username);
    sprintf(remString, "rm '/tmp/#%s' 2> /dev/null", username);
    system(remString);
    unlink(saddr.sa_data);
    saddr.sa_family = AF_UNIX;
    s = socket(AF_UNIX, SOCK_STREAM, 0);
    bind(s, &saddr, sizeof(saddr));
    listen(s, 1);
    while (TRUE) {
        rfd = accept(s, NULL, NULL);
        rf = fdopen(rfd, "r");
        while ((ch = getc(rf)) != EOF)
        putchar(ch);
        fclose(rf);
        fflush(stdout);
    }
    return 0;
}