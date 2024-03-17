#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "swarm.h"

const u32 max = 100000000; // 100mil = 100%
int global_best = 0;       // initialize Global variable to store global best

swarm **init_swarm_collection()
{
    swarm **swarm_collection = (swarm **)malloc(10 * sizeof(swarm *));
    for (int i = 0; i < 10; i++)
    {
        swarm_collection[i] = init_swarm(i); // Initialize each swarm in the collection
    }
    return swarm_collection;
}

swarm *init_swarm(int seed)
{
    const float min_value = 0.0;
    const float max_value = 1.0;

    swarm *new_swarm = (swarm *)malloc(sizeof(swarm));
    new_swarm->distribution = (u32 **)malloc(15 * sizeof(u32 *));
    new_swarm->localbest = (u32 **)malloc(15 * sizeof(u32 *));
    new_swarm->velocity = (u32 **)malloc(15 * sizeof(u32 *));
    new_swarm->score = 0;
    new_swarm->bestscore = 0;
    new_swarm->weights = 0.5;
    new_swarm->rand_displacement = min_value + ((max_value - min_value) * ((float)rand() / RAND_MAX)); // generate a random number between 0 and 1

    srand(seed); // Set the seed for random number generation

    u32 total = 0;
    for (int i = 0; i < 15; i++)
    {
        new_swarm->distribution[i] = (u32 *)malloc(sizeof(u32));
        new_swarm->distribution[i][0] = rand() % max; // Generate a random distribution probability
        total += new_swarm->distribution[i][0];
    }

    // Normalize the distribution probabilities to sum up to max
    for (int i = 0; i < 15; i++)
    {
        new_swarm->distribution[i][0] = (new_swarm->distribution[i][0] * max) / total;
    }

    return new_swarm;
}

int swarm_havoc(swarm *target)
{
    u32 **distribution = target->distribution;
    int rand = random() % max;
    // int rand = UR(max + 1);
    for (int i = 0; i < 15; i++)
    {
        if (rand < distribution[i][0])
        {
            return i;
        }
        rand -= distribution[i][0];
    }
    return -1;
}

swarm *compare_swarm(swarm **swarm_collection)
{
    // initialize best_swarm to the first swarm in the collection
    swarm *best_swarm = swarm_collection[0];

    // iterate through all the swarms in swarm_collection and compare their scores
    // Update the best swarm if a higher score is found
    for (int i = 1; swarm_collection[i] != NULL; i++)
    {
        if (swarm_collection[i]->bestscore > best_swarm->bestscore)
        {
            best_swarm = swarm_collection[i];
        }
    }

    return best_swarm;
}

void update_localbest(swarm *swarm)
{
    if (swarm->score > swarm->bestscore)
    {
        for (int i = 0; i < 15; i++)
        {
            swarm->localbest[i][0] = swarm->distribution[i][0];
        }
    }
}

void update_bestscore(swarm *swarm)
{
    if (swarm->score > swarm->bestscore)
    {
        swarm->bestscore = swarm->score;
    }
}

void update_velocity(swarm *swarm)
{
    for (int i = 0; i < 15; i++)
    {
        swarm->velocity[i][0] = (u32)(swarm->weights * swarm->velocity[i][0] + swarm->rand_displacement * (swarm->localbest[i][0] - swarm->distribution[i][0]) + swarm->rand_displacement * (global_best - swarm->distribution[i][0]));
    }
}

void update_distribution(swarm *swarm)
{
    for (int i = 0; i < 15; i++)
    {
        swarm->distribution[i][0] += swarm->velocity[i][0];
    }
}

void optimise(swarm *swarm)
{
    // TODO
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