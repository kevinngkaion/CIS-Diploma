/* send.c -- socket demo which acts as a message client */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
struct sockaddr saddr;
int s, ch;
FILE *sf;
int main(int argc, char *args[]) {
    char username[15];
    if (argc != 2) {
        fprintf(stderr, "Usage: %s recipient\n", args[0]);
        exit(1);
    }
    strcpy(username, getenv("LOGNAME"));
    strcpy(saddr.sa_data, "/tmp/#");
    strcat(saddr.sa_data, args[1]);
    s = socket(AF_UNIX, SOCK_STREAM, 0);
    saddr.sa_family = AF_UNIX;
    connect(s, &saddr, sizeof(saddr));
    sf = fdopen(s, "w");
    fprintf(sf, "Data from %s:\n", username);
    while ((ch = getchar()) != EOF)
        putc(ch, sf);
    fclose(sf);
    return 0;
}