#ifndef _HAVE_SWARM
#define _HAVE_SWARM

//Funcs defined in afl-fuzz to be used in swarm.c
// inline u32 UR(u32 limit);

typedef struct leparticle {
    float** weights;
    u32** distribution;
    u32** localbest;
    u32** mutscore;
    u32 velocity;
    u8 score;
    u8 bestscore;
} particle;

//Funcs defined in swarm.c

/* Initialise all particles*/
particle** init_swarm();

/* Initialise an individual particle struct with all variables*/
particle* init_particle();

/* Essentially does the same thing as and replaces the switch part of original havoc stage
Instead of a uniform distribution, it uses the provided swarm distribution to select mutation operators*/
int swarm_havoc(particle* target);

/* Compares the score of swarms and returns best swarm*/
particle* compare_swarm(particle** swarm);

/* check if new score is a new best score then update localbest distribution*/
void update_localbest(particle** swarm);

/* Optimise and Update distributions for all swarms
Obtain gbest (distribution) by comparing swarms,
Updates velocity then updates distribution*/
void optimise(particle** swarm);

/*TODO figure out how to store data from fuzzing to update scores*/


#endif