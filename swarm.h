#ifndef _HAVE_SWARM
#define _HAVE_SWARM

//Funcs defined in afl-fuzz to be used in swarm.c
// inline u32 UR(u32 limit);

typedef struct leswarm {
    u32** distribution;
    u32** localbest;
    u32 velocity;
} swarm;

//Funcs defined in swarm.c
int swarm_havoc(swarm* target);

#endif