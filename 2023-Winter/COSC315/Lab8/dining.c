/*
    Kevin Ngkaion
    OC# 300325759
    COSC-315 Lab 8

    Answers to Exercise 1:
    a)  2 philosophers can be eating at a given time
    b)  5 philosophers can be eating at a given time with 10 philosophers and 10 chopsticks
    c)  1 philosopher can be eating at a given time with 3 philosophers and 3 chopsticks
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* the commands that can be applied */
enum commands {
    THINK, GRAB_LEFT, GRAB_RIGHT, EAT, DROP
};

// define the size
#define SIZE 5

/* The state of the game */
struct dining {
    /* how many philosophers */
    int tableCount;

    /* set to 0 if not in deadlock, 1 if currently deadlocked */
    int deadlockWarning;

    /* the left chopstick is the same number as the player, the right is the next chopstick
     * -1 indicates previous player holds chopstick, 0 means free, 1 means that seat holds chopstick. */
    int *chopsticks;

    /* how much energy each philosopher has */
    int *philosopherEnergy;

    /* how much successful thinking each philosopher has done */
    int *philosopherScore;

    /* the order that actions took place last round - internal */
    int *lastRunOrder;

    /* the agent in control of a particular seat */
    int (**agents)(struct dining*, int);
};

/* your most basic of AIs */
int AI_Basic(struct dining *game, int seat) {
    int hasLeft = game->chopsticks[seat] > 0;
    int hasRight = game->chopsticks[(seat + 1) % game->tableCount] < 0;
    //printf("Basic AI seat %d: hasLeft - %d  |  hasRight - %d\n\n", seat, hasLeft, hasRight);
    if ((hasLeft) && (hasRight))
        return EAT;
    if (hasLeft)
        return GRAB_RIGHT;
    if (rand()%2)
        return GRAB_LEFT;
    return THINK;
}

// AI to ensure that a deadlock does not occur
int AI_AntiDeadlock(struct dining *game, int seat) {
    int hasLeft = game->chopsticks[seat] > 0;
    int hasRight = game->chopsticks[(seat + 1) % game->tableCount] < 0;
    //printf("AI seat %d: hasLeft - %d  |  hasRight - %d\n\n", seat, hasLeft, hasRight);
    if (game->deadlockWarning)
        return DROP;
    if ((hasLeft) && (hasRight))
        return EAT;
    if (hasLeft)
        return GRAB_RIGHT;
    if (rand()%2)
        return GRAB_LEFT;
    return THINK;
}

// Helper to get the min and max score currently in the game
int getMinMaxScore(struct dining *game, int opt){
    int min, max, score;
    min = max = game->philosopherScore[0];
    for (int i = 1; i < game->tableCount; i++){
        score = game->philosopherScore[i];
        if (score < min)
            min = score;
        if (score > max)
            max = score;
    }
    return opt == 1 ? max : min;
}

// Helper to check if it is a tie game
int isTied(struct dining* game){
    int max = getMinMaxScore(game, 1);
    int count = 0;
    for (int i = 0; i < game->tableCount; i++){
        //printf("i = %d\nMAX = %d | current Phil score = %d\n", i, max, game->philosopherScore[i]);
        if (max == game->philosopherScore[i]){
            count++;
            //printf("Count is now %d\n", count);
        }
    }
    return count > 1 ? 1 : 0;
}


// My AI that will win
int AI_ThatWillWin(struct dining *game, int seat) {
    int left = game->chopsticks[seat];
    int prevLeft = game->chopsticks[(seat + 4) % game->tableCount];
    int right = game->chopsticks[(seat + 1) % game->tableCount];
    int nextRight = game->chopsticks[(seat + 2) % game->tableCount];
    int hasLeft = left > 0;
    int hasRight = right < 0;
    int myEnergy = game->philosopherEnergy[seat];
    int myScore = game->philosopherScore[seat];
    //printf("AI seat %d: hasLeft - %d  |  hasRight - %d\n\n", seat, hasLeft, hasRight);
    if ((hasLeft) && (hasRight)){
        //printf("I have left and right so I will EAT\n");
        return EAT;
    }
    if (myEnergy >= 3){
        //printf("I have 3 or more energy so I will THINK\n");
        return THINK;
    }
    if ((hasLeft || hasRight) && (myScore < getMinMaxScore(game, 1) || isTied(game))){
        // printf("I have either left or right\n");
        // printf("I am the leading scorer: %d\n", myScore == getMinMaxScore(game, 1));
        // printf("The game is tied: %d\n", isTied(game));
        if (game->deadlockWarning){
            //printf("Game is in a deadlock and I am not winning so I need to DROP");
            return DROP;
        }
    }
    if (hasLeft){
        //printf("I have left so I will try to GRAB RIGHT\n");
        return GRAB_RIGHT;
    }
    if (hasRight){
        //printf("I have right so I will try to GRAB LEFT\n");
        return GRAB_LEFT;
    }
    if (nextRight == -1 && right == 0){
        //printf("Person on my right has grabbed their right so I will try to GRAB RIGHT\n");
        return GRAB_RIGHT;
    }
    if (prevLeft == 1 && left == 0){
        //printf("Person on my left has grabbed their left so I will try to GRAB LEFT\n");
        return GRAB_LEFT;
    }
    if (right == 0){
        //printf("None of the other conditions have been met and my right is free so I will try to GRAB RIGHT\n");
        return GRAB_RIGHT;
    }
    if (left == 0){
        //printf("None of the other conditions have been met and my left is free so I will try to GRAB LEFT\n");
        return GRAB_LEFT;
    }
    //printf("I have nothing else to do and I am not holding any chopsticks so I will THINK\n");
    return THINK;
}

/* constructor for creating the game instance */
struct dining* createTable(int size) {
    struct dining * table = (struct dining *)malloc(sizeof(struct dining));
    table->tableCount = size;
    table->deadlockWarning = 0;
    table->chopsticks = (int *)malloc(sizeof(int) * size);
    table->philosopherEnergy = (int *)malloc(sizeof(int) * size);
    table->philosopherScore = (int *)malloc(sizeof(int) * size);
    table->lastRunOrder = (int *)malloc(sizeof(int) * size);
    table->agents = malloc(sizeof(int(**)(struct dining*, int)) * size);
    for (int i = 0; i < size; ++i) {
        table->chopsticks[i] = 0;
        table->philosopherEnergy[i] = 3;
        table->philosopherScore[i] = 0;
        table->lastRunOrder[i] = i;
        table->agents[i] = AI_Basic;
    }
    return table;
}

/* copy state of one game to another
 * used to prevent agents from altering the game state
 */
void cloneTable(struct dining *src, struct dining *dest) {
    dest->deadlockWarning = src->deadlockWarning;
    for (int i = 0; i < src->tableCount; ++i) {
        dest->chopsticks[i] = src->chopsticks[i];
        dest->philosopherEnergy[i] = src->philosopherEnergy[i];
        dest->philosopherScore[i] = src->philosopherScore[i];
        dest->lastRunOrder[i] = src->lastRunOrder[i];
        dest->agents[i] = src->agents[i];
    }
}

/* destructor for cleaning up memory when game is done */
void destroyTable(struct dining *game) {
    free(game->chopsticks);
    free(game->philosopherEnergy);
    free(game->philosopherScore);
    free(game->lastRunOrder);
    free(game->agents);
    free(game);
}

/* Check for a deadlock. This requires two things be checked
 * (hint philosophers and chopsticks)
 * If no deadlock is detected set game's deadlock warning to 0;
 * If detected, and warning is 0 set it to 1
 * if detected and warning is 1 then return 1 to indicate deadlock.
 */
int isDeadlock(struct dining *game) {
    int thisVal, nextVal;
    //  check if each all the chopsticks have the same value by comparing this with next.
    for (int i = 0; i < game->tableCount-1; i++){
        thisVal = game->chopsticks[i];
        nextVal = game->chopsticks[i+1];
        if (thisVal == 0 || thisVal != nextVal){
            game->deadlockWarning = 0;
            return 0;
        }
    }
    if (!game->deadlockWarning){
        //printf("######DEADLOCK WARNING######\n");
        game->deadlockWarning = 1;
        return 0;
    }
    //printf("######GAME OVER######\n");
    return 1;
}

/* prints the current state of the table */
void printDining(struct dining *game) {
    for (int i = 0; i < game->tableCount; ++i) {
        char ch = (game->chopsticks[i] == 0) ? '|' : ((game->chopsticks[i] == -1) ? '\\' : '/');
        printf(" %c %d", ch, game->philosopherEnergy[i]);
    }
    printf("\n");
    for (int i = 0; i < game->tableCount; ++i) {
        printf(" %03d", game->philosopherScore[i]);
    }
    printf("\n");

}

/* Utility method to scramble a list of integers */
void scramble(int *list, int n) {
    int swap, temp;
    for (int i = 0; i < (n-1); ++i) {
        swap = i + (rand() % (n-i));
        temp = list[swap];
        list[swap] = list[i];
        list[i] = temp;
    }
}

/* Handles the gameplay */
void runRound(struct dining *game) {
    scramble(game->lastRunOrder, game->tableCount);
    struct dining *clone = createTable(game->tableCount);
    for (int i = 0; i < game->tableCount; ++i) {
        cloneTable(game, clone);
        int seat = game->lastRunOrder[i];
        int cmd = game->agents[seat](clone, seat);
        switch (cmd) {
            case THINK:
                if (    (game->philosopherEnergy[seat] > 0) && // has energy
                        (game->chopsticks[seat] < 1) && // not holding left chopstick
                        (game->chopsticks[(seat + 1) % game->tableCount] > -1) // right
                   ) {
                   --game->philosopherEnergy[seat] ;
                   ++game->philosopherScore[seat];
                }
                break;
            case GRAB_LEFT:
                if (game->chopsticks[seat] == 0)
                    game->chopsticks[seat] = 1;
                break;
            case GRAB_RIGHT:
                if (game->chopsticks[(seat + 1) % game->tableCount] == 0)
                    game->chopsticks[(seat + 1) % game->tableCount] = -1;
                break;
            case EAT:
                if  ( (game->chopsticks[seat] == 1) && // holding left chopstick
                      (game->chopsticks[(seat + 1) % game->tableCount] == -1) // right
                    ) {
                    game->philosopherEnergy[seat] += 3;
                    if (game->philosopherEnergy[seat] > 5)
                        game->philosopherEnergy[seat] = 5;
                    game->chopsticks[seat] = 0;
                    game->chopsticks[(seat + 1) % game->tableCount] = 0;
                }
                break;
            case DROP:
                if (game->chopsticks[seat] == 1)
                    game->chopsticks[seat] = 0;
                if (game->chopsticks[(seat + 1) % game->tableCount] == -1)
                    game->chopsticks[(seat + 1) % game->tableCount] = 0;
                break;
            default:
                printf("Agent for seat %d issued unknown command %d\n", seat, cmd);
        }
    }
    destroyTable(clone);
}

int getWinner(struct dining* game){
    int highScore = getMinMaxScore(game, 1);
    for (int i = 0; i < game->tableCount; i++){
        if (game->philosopherScore[i] == highScore)
            return i;
    }
    return -1;
}

void printResults(struct dining* game){
    int highScore = getMinMaxScore(game, 1);
    for (int i = 0; i < game->tableCount; i++){
        printf("Player %d Final Score: %d\n", i, game->philosopherScore[i]);
        if (game->philosopherScore[i] == highScore)
            printf("***PLAYER %d IS THE WINNER***\n\n", i);
    }
}

int main() {
    int winCountList[SIZE];
    for (int i = 0; i < SIZE; i++){
        winCountList[i] = 0;
    }
    for (int i = 0; i < 100000; i++){
        struct dining *game = createTable(SIZE);
        time_t t;
        srand((unsigned int)time(&t));

        // SET AGENTS YOU WANT TO USE HERE
        game->agents[0] = AI_ThatWillWin;
        game->agents[1] = AI_Basic;
        game->agents[2] = AI_Basic;
        game->agents[3] = AI_Basic;
        game->agents[4] = AI_Basic;

        int round = 1;
        while ((round <= 100000) && ( !isDeadlock(game))) {
            //printf("* round %d *\n", round++);
            runRound(game);
            //printDining(game);
        }
        int winner = getWinner(game);
        if (winner >= 0)
            winCountList[winner]++;
        //printResults(game);
        destroyTable(game);
    }
    printf("---RESULTS---\n");
    for (int i = 0; i < SIZE; i++){
        printf("Philosopher %d: %d wins\n", i, winCountList[i]);
    }
    return 0;
}
