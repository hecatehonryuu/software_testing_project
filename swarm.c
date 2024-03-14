#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "swarm.h"

const u32 max = 100000000; //100mil = 100%

swarm** init_swarm_collection(){
    //TODO
    return NULL;
}

swarm* init_swarm(){
    //TODO
    return NULL;
}

int swarm_havoc(swarm* target) {
    u32** distribution = target->distribution;
    int rand = random() % max; 
    // int rand = UR(max + 1); 
    for (int i = 0; i < 15; i++) {
        if (rand < distribution[i][0]) {
            return i;
        }
        rand -= distribution[i][0];
    }
    return -1;
}

swarm* compare_swarm(swarm** collection){
    //TODO
    return NULL;
}

void update_localbest(swarm** collection){
    //TODO
    return NULL;
}

void optimise(swarm** collection){
    //TODO
    return NULL;
}

/*
int main () {
    u32 x = 100000000/10;
    u32** swarm = (u32**)malloc(15 * sizeof(u32*));
    for (int i = 0; i < 15; i++) {
        swarm[i] = (u32*)malloc(2 * sizeof(u32));
        swarm[i][0] = x;
    }

    int** array = (int**)malloc(15 * sizeof(int*));
    for (int i = 0; i < 15; i++) {
        array[i] = (int*)malloc(2 * sizeof(int));
        array[i][0] = 0;
    }

    for (int i = 0; i < 10000; i++) {
        int mutoper = swarm_havoc(swarm);
        array[mutoper][0]++;
    }
    
    for (int i = 0; i < 15; i++) {
        printf("%d, ", array[i][0]);
    }
    printf("\n");

    return 0;
}
*/