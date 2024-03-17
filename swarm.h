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

    float rand_displacement; /* random displacement between 0 and 1 */

    float weights; /* weight is a constant value */
} swarm;

/* Funcs defined in swarm.c */

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
/* TODO: what if new score == best score ? do we still update the localbest distribution? erase this comment if this question is solved*/
void update_localbest(swarm *swarm);

/* check if new score is higher than best score, if it is then we update best score*/
void update_bestscore(swarm *swarm);

/* update the velocity of every mutator in swarm */
void update_velocity(swarm *swarm);

/* update the distribution probability of every mutator in swarm */
void update_distribution(swarm *swarm);

/* Optimise and Update distributions for all swarms
Obtain gbest (distribution) by comparing swarms,
Updates velocity then updates distribution*/
void optimise(swarm *swarm);

/*TODO figure out how to store data from fuzzing to update scores*/

#endif