#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "swarm.h"

const u32 max = 100000000; // 100mil = 100%
const int numswarms = 10;

swarm **init_swarm_collection()
{
    int seed = 123;
    swarm **swarm_collection = (swarm **)malloc(numswarms * sizeof(swarm *));
    for (int i = 0; i < numswarms; i++)
    {
        swarm_collection[i] = init_swarm(seed); // Initialize each swarm in the collection
    }
    return swarm_collection;
}

swarm *init_swarm(int seed)
{
    swarm *new_swarm = (swarm *)malloc(sizeof(swarm));
    new_swarm->distribution = (u32 **)malloc(15 * sizeof(u32 *));
    new_swarm->localbest = (u32 **)malloc(15 * sizeof(u32 *));
    new_swarm->velocity = (u32 **)malloc(15 * sizeof(u32 *));
    new_swarm->score = 0;
    new_swarm->bestscore = 0;
    new_swarm->weights = 0.5; // TODO to determine weight to use, verify math works correctly with floats and u32
    srand(seed);              // Set the seed for random number generation

    u32 total = 0;
    for (int i = 0; i < 15; i++)
    {
        new_swarm->distribution[i] = (u32 *)malloc(sizeof(u32));
        new_swarm->localbest[i] = (u32 *)malloc(sizeof(u32));
        new_swarm->velocity[i] = (u32 *)malloc(sizeof(u32));
        new_swarm->distribution[i][0] = ((double)rand() / RAND_MAX) * max; // Generate a random distribution probability
        total += new_swarm->distribution[i][0];
    }

    // Normalize the distribution probabilities to sum up to max
    for (int i = 0; i < 15; i++)
    {
        new_swarm->distribution[i][0] = (new_swarm->distribution[i][0] * max) / total; // TODO verify math works correctly with u32
    }

    return new_swarm;
}

void free_swarm_collection(swarm **swarm_collection)
{
    for (int i = 0; i < numswarms; i++)
    {
        free_swarm(swarm_collection[i]);
    }
    free(swarm_collection);
}

void free_swarm(swarm *swarm)
{
    for (int i = 0; i < 15; i++)
    {
        free(swarm->distribution[i]);
        free(swarm->localbest[i]);
        free(swarm->velocity[i]);
    }
    free(swarm->distribution);
    free(swarm->localbest);
    free(swarm->velocity);
    free(swarm);
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

void update_best_swarm(swarm **swarm_collection, swarm *best_swarm)
{
    // initialize best_swarm to the first swarm in the collection
    swarm *temp_swarm = swarm_collection[0];

    // iterate through all the swarms in swarm_collection and compare their scores
    // Update the best swarm if a higher score is found
    for (int i = 1; swarm_collection[i] != NULL; i++)
    {
        if (swarm_collection[i]->bestscore > temp_swarm->bestscore)
        {
            temp_swarm = swarm_collection[i];
        }
    }

    best_swarm = temp_swarm;
}

void update_localbest(swarm **swarm_collection)
{
    for (int i = 0; i < numswarms; i++)
    {
        swarm *swarm = swarm_collection[i];
        if (swarm->score > swarm->bestscore)
        {
            swarm->bestscore = swarm->score;
            for (int i = 0; i < 15; i++)
            {
                swarm->localbest[i][0] = swarm->distribution[i][0];
            }
        }
    }
}

void update_distribution(swarm **swarm_collection, swarm *best_swarm)
{
    u32** global_best = best_swarm->distribution;

    for (int i = 0; i < numswarms; i++)
    {
        swarm *swarm = swarm_collection[i];
        for (int i = 0; i < 15; i++)
        {
            swarm->velocity[i][0] = (u32)(swarm->weights * swarm->velocity[i][0] + rand() / RAND_MAX * (swarm->localbest[i][0] - swarm->distribution[i][0]) + rand() / RAND_MAX * (global_best[i][0] - swarm->distribution[i][0]));
            swarm->distribution[i][0] += swarm->velocity[i][0];
        }
    }
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