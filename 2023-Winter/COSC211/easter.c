#include <stdio.h>

int main(){
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);

    int g = (year % 19) + 1;
    int c = (year / 100) + 1;
    int x = (3 * c / 4) - 12;
    int z = (((8 * c) + 5) / 25) - 5;
    int d = (5 * year / 4) - x - 10;
    int epact = ((11 * g) + 20 + z - x) % 30;
    if ((epact == 25 && g > 11) || epact == 24)
        epact++;
    int n = 44 - epact;
    if (n < 21)
        n += 30;
    n = n + 7 - ((d + n) % 7);
    int m;
    if (n > 31){
        m = 4;
        n -= 31;
    } else
        m = 3;
    char* month;
    if (m == 3)
        month = "March";
    else if (m == 4)
        month = "April";
    printf("Easter Sunday is on %s %d, %d\n", month, n, year);
}