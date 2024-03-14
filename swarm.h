#ifndef _HAVE_SWARM
#define _HAVE_SWARM

//Funcs defined in afl-fuzz to be used in swarm.c
// inline u32 UR(u32 limit);

typedef struct leswarm {
    float** weights;
    u32** distribution;
    u32** localbest;
    u32** mutscore;
    u32 velocity;
    u8 score;
    u8 bestscore;
} swarm;

//Funcs defined in swarm.c

/* Initialise all swarms*/
swarm** init_swarm_collection();

/* Initialise an individual swarm struct with all variables*/
swarm* init_swarm();

/* Essentially does the same thing as and replaces the switch part of original havoc stage
Instead of a uniform distribution, it uses the provided swarm distribution to select mutation operators*/
int swarm_havoc(swarm* target);

/* Compares the score of swarms and returns best swarm*/
u32** compare_swarm(swarm** collection);

/* check if new score is a new best score then update localbest distribution*/
void update_localbest(swarm** collection);

/* Something to calculate Gbest. how???*/

/* Calculate and update velocties for all swarms*/
void update_velocity(swarm** collection, u32** gbest);

/* Calculate and update distribution for all swarms*/
void update_distribution(swarm** collection);

/* Optimise and Update distributions for all swarms
Calculates Gbest first (To add arg for however gbest is calculated)
Updates velocity then updates distribution*/
void optimise(swarm** collection);


#endif