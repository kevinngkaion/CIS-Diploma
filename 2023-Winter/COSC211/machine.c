#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int stop();
int load(int address, int** memory);
int store(int address, int** memory);
int add(int address, int** memory);
int sub(int address, int** memory);
int mult(int address, int** memory);
int divide(int address, int** memory);
int in(int address, int** memory);
int out(int address, int** memory);
int br(int address);
int bgte(int address);
int load_instructions(int** memory, int* instructions, int size);

int acc, pc, ir, on;
int main(){
    int* memory = (int*)malloc(100*sizeof(int)); // create an int array of size 100
    acc = pc = ir = 0;
    on = 1;

    // initializing memory values
    memory[99] = -2;
    memory[98] = memory[97] = memory[96] = memory[95] = memory[94] = 0;
    memory[93] = 64;
    memory[92] = 8;
    memory[91] = -2;
    memory[90] = 1;
    memory[89] = 14;
    memory[88] = 56;

    // creating array for machine code instructions;
    int instructions[32] = {
        191,
        591,
        591,
        296,
        191,
        591,
        589,
        295,
        191,
        588,
        294,
        196,
        495,
        394,
        493,
        297,
        498,
        1027,
        191,
        390,
        291,
        192,
        491,
        1000,
        925,
        898,
        0,
        197,
        298,
        191,
        299,
        918
    };
    // int i;
    int size = sizeof(instructions)/sizeof(instructions[0]);
    // for(i = 0; i < size; i++){
    //     memory[i] = instructions[i];
    // }
    load_instructions(&memory, instructions, size);
    //Begin reading through the memory array
    while (on == 1){
        ir = memory[pc];
        pc++;
        int instruction = ir / 100;
        int address = ir % 100;
        switch (instruction) {
            case 0:
                stop();
                break;
            case 1: // load
                load(address, &memory);
                break;
            case 2: // store
                store(address, &memory);
                break;
            case 3: // add
                add(address, &memory);
                break;
            case 4: // sub
                sub(address, &memory);
                break;
            case 5: // mult
                mult(address, &memory);
                break;
            case 6: // divide
                divide(address, &memory);
                break;
            case 7: // in
                in(address, &memory);
                break;
            case 8: // out
                out(address, &memory);
                break;
            case 9: // br
                br(address);
                break;
            case 10: // bgte
                bgte(address);
                break;
        }
    }

}

int stop(){
    on = 0;
    return on;
}

int load(int address, int** memory){
    acc = (*memory)[address];
    return 0;
}

int store(int address, int** memory){
    (*memory)[address] = acc;
    return 0;
}

int add(int address, int** memory){
    acc += (*memory)[address];
    return 0;
}

int sub(int address, int** memory){
    acc -= (*memory)[address];
    return 0;
}

int mult(int address, int** memory){
    acc *= (*memory)[address];
    return 0;
}

int divide(int address, int** memory){
    acc /= (*memory)[address];
    return 0;
}

int in(int address, int** memory){
    int input;
    printf("Input a number: ");
    scanf("%d\n", &input);
    (*memory)[address] = input;
    return 0;
}

int out(int address, int** memory){
    printf("The output is: %d\n", (*memory)[address]);
    return 0;
}

int br(int address){
    pc = address;
    return 0;
}

int bgte(int address){
    if(acc >= 0){
        pc = address;
    }
    return 0;
}

int load_instructions(int** memory, int* instructions, int size){
    int i;
    for(i = 0; i < size; i++){
        (*memory)[i] = instructions[i];
    }
}