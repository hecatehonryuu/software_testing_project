#ifndef _HAVE_SWARM
#define _HAVE_SWARM

// Funcs defined in afl-fuzz to be used in swarm.c
//  inline u32 UR(u32 limit);

typedef struct leswarm
{
    u32 **distribution; // an array of 15 distribution probabilities for every mutator
    u32 **localbest;    // an array of 15 probabilities (of this particle) that resulted in the most interesting test cases for every swarm
    // u32 **mutscore;
    u32 **velocity; // an array of 15 velocities for every mutator
    u8 score;       // total score
    u8 bestscore;
    float weights; // weight is a constant value
} swarm;

// Funcs defined in swarm.c

/* Initialise all swarms*/
swarm **init_swarm_collection();

/* Initialise a swarm struct with all variables*/
swarm *init_swarm();

/* Essentially does the same thing as and replaces the switch part of original havoc stage
Instead of a uniform distribution, it uses the provided swarm distribution to select mutation operators*/
int swarm_havoc(swarm *target);

/* Compares the score of swarms and returns best swarm*/
swarm *compare_swarm(swarm **swarm_collection);

/* check if new score is a new best score then update localbest distribution*/
void update_localbest(swarm *swarm);

/* Optimise and Update distributions for all swarms
Obtain gbest (distribution) by comparing swarms,
Updates velocity then updates distribution*/
void optimise(swarm *swarm);

/*TODO figure out how to store data from fuzzing to update scores*/

#endif