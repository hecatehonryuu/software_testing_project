#ifndef _HAVE_SWARM
#define _HAVE_SWARM

/* Funcs defined in afl-fuzz to be used in swarm.c */
/* inline u32 UR(u32 limit); */

typedef struct leswarm
{
    u32 **distribution; /* an array storing the distribution probabilities of 15 mutators */

    u32 **localbest; /* an array storing the distribution probability that resulted in the most interesting test cases for every mutator (for this particular swarm) */

    u32 **velocity; /* an array storing the velocity of each mutator */

    u8 score; /* total score */

    u8 bestscore;

    float weights; /* weight is a constant value */
} swarm;

/* Funcs defined in swarm.c */

/* Initialise all swarms*/
swarm **init_swarm_collection();

/* Initialise a swarm struct with all variables*/
swarm *init_swarm();

void free_swarm_collection(swarm **swarm_collection);

/* Essentially does the same thing as and replaces the switch part of original havoc stage
Instead of a uniform distribution, it uses the provided swarm distribution to select mutation operators*/
int swarm_havoc(swarm *target);

/* Compares the score of swarms and returns best swarm*/
swarm *compare_swarm(swarm **swarm_collection);

/* check if new score is a new best score then update localbest distribution & best score*/
void update_localbest(swarm **swarm_collection);

/* update the velocity & distribution of every mutator in swarm */
void update_distribution(swarm **swarm_collection, u32 **global_best);

/* compare the localbest of all mutators in every swarm and update the global best with the localbest that has the highest score*/
void update_globalbest(swarm *best_swarm, swarm **swarm_collection, u32 **global_best);

/* Optimise and Update distributions for all swarms
Obtain gbest (distribution) by comparing swarms,
Updates velocity then updates distribution*/
void optimise(swarm **swarm_collection, u32 **global_best);

/*TODO figure out how to store data from fuzzing to update scores*/

#endif