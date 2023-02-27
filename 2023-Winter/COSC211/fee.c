#include <stdio.h>


void mem(int *memory)
{
    memory[0]=100;


}
int main(){
    int memory[100];
    int tsety=0;
    mem(memory);
    printf("%d\n",memory[0]);

    return 0;
}